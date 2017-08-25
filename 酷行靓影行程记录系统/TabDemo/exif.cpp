/*
 * File:	exif.cpp
 * Purpose:	cpp EXIF reader
 * 16/Mar/2003 <ing.davide.pizzolato@libero.it>
 * based on jhead-1.8 by Matthias Wandel <mwandel(at)rim(dot)net>
 */
#include "stdafx.h"
#include "exif.h"

////////////////////////////////////////////////////////////////////////////////
Cexif::Cexif(EXIFINFO* info)
{
	if (info) {
		m_exifinfo = info;
		freeinfo = false;
	} else {
		m_exifinfo = new EXIFINFO;
		memset(m_exifinfo,0,sizeof(EXIFINFO));
		freeinfo = true;
	}

	m_szLastError[0]='\0';
	ExifImageWidth = MotorolaOrder = 0;
	SectionsRead=0;
	memset(&Sections, 0, MAX_SECTIONS * sizeof(Section_t));
}
////////////////////////////////////////////////////////////////////////////////
Cexif::~Cexif()
{
	for(int i=0;i<MAX_SECTIONS;i++) if(Sections[i].Data) free(Sections[i].Data);
	if (freeinfo) delete m_exifinfo;
}
////////////////////////////////////////////////////////////////////////////////
bool Cexif::DecodeExif(FILE * hFile)
{
    int a;
    int HaveCom = 0;

    a = fgetc(hFile);

    if (a != 0xff || fgetc(hFile) != M_SOI){
        return 0;
    }

    for(;;){
        int itemlen;
        int marker = 0;
        int ll,lh, got;
        unsigned char * Data;

        if (SectionsRead >= MAX_SECTIONS){
			strcpy(m_szLastError,"Too many sections in jpg file");
			return 0;
        }

        for (a=0;a<7;a++){
            marker = fgetc(hFile);
            if (marker != 0xff) break;

            if (a >= 6){
                printf("too many padding unsigned chars\n");
                return 0;
            }
        }

        if (marker == 0xff){
            // 0xff is legal padding, but if we get that many, something's wrong.
            strcpy(m_szLastError,"too many padding unsigned chars!");
			return 0;
        }

        Sections[SectionsRead].Type = marker;

        // Read the length of the section.
        lh = fgetc(hFile);
        ll = fgetc(hFile);

        itemlen = (lh << 8) | ll;

        if (itemlen < 2){
            strcpy(m_szLastError,"invalid marker");
			return 0;
        }

        Sections[SectionsRead].Size = itemlen;

        Data = (unsigned char *)malloc(itemlen);
        if (Data == NULL){
            strcpy(m_szLastError,"Could not allocate memory");
			return 0;
        }
        Sections[SectionsRead].Data = Data;

        // Store first two pre-read unsigned chars.
        Data[0] = (unsigned char)lh;
        Data[1] = (unsigned char)ll;

        got = fread(Data+2, 1, itemlen-2,hFile); // Read the whole section.
        if (got != itemlen-2){
            strcpy(m_szLastError,"Premature end of file?");
			return 0;
        }
        SectionsRead += 1;

        switch(marker){

            case M_SOS:   // stop before hitting compressed data 
                // If reading entire image is requested, read the rest of the data.
                /*if (ReadMode & READ_IMAGE){
                    int cp, ep, size;
                    // Determine how much file is left.
                    cp = ftell(infile);
                    fseek(infile, 0, SEEK_END);
                    ep = ftell(infile);
                    fseek(infile, cp, SEEK_SET);

                    size = ep-cp;
                    Data = (uchar *)malloc(size);
                    if (Data == NULL){
                        strcpy(m_szLastError,"could not allocate data for entire image");
						return 0;
                    }

                    got = fread(Data, 1, size, infile);
                    if (got != size){
                        strcpy(m_szLastError,"could not read the rest of the image");
						return 0;
                    }

                    Sections[SectionsRead].Data = Data;
                    Sections[SectionsRead].Size = size;
                    Sections[SectionsRead].Type = PSEUDO_IMAGE_MARKER;
                    SectionsRead ++;
                    HaveAll = 1;
                }*/
                return 1;

            case M_EOI:   // in case it's a tables-only JPEG stream
                printf("No image in jpeg!\n");
                return 0;

            case M_COM: // Comment section
                if (HaveCom){
                    // Discard this section.
                    free(Sections[--SectionsRead].Data);
					Sections[SectionsRead].Data=0;
                }else{
                    process_COM(Data, itemlen);
                    HaveCom = 1;
                }
                break;

            case M_JFIF:
                // Regular jpegs always have this tag, exif images have the exif
                // marker instead, althogh ACDsee will write images with both markers.
                // this program will re-create this marker on absence of exif marker.
                // hence no need to keep the copy from the file.
                free(Sections[--SectionsRead].Data);
				Sections[SectionsRead].Data=0;
                break;

            case M_EXIF:
                // Seen files from some 'U-lead' software with Vivitar scanner
                // that uses marker 31 for non exif stuff.  Thus make sure 
                // it says 'Exif' in the section before treating it as exif.
                if (memcmp(Data+2, "Exif", 4) == 0){
                    m_exifinfo->IsExif = process_EXIF((unsigned char *)Data+2, itemlen);
                }else{
                    // Discard this section.
                    free(Sections[--SectionsRead].Data);
					Sections[SectionsRead].Data=0;
                }
                break;

            case M_SOF0: 
            case M_SOF1: 
            case M_SOF2: 
            case M_SOF3: 
            case M_SOF5: 
            case M_SOF6: 
            case M_SOF7: 
            case M_SOF9: 
            case M_SOF10:
            case M_SOF11:
            case M_SOF13:
            case M_SOF14:
            case M_SOF15:
                process_SOFn(Data, marker);
                break;
            default:
                // Skip any other sections.
                //if (ShowTags) printf("Jpeg section marker 0x%02x size %d\n",marker, itemlen);
                break;
        }
    }
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Process a EXIF marker
   Describes all the drivel that most digital cameras include...
--------------------------------------------------------------------------*/
bool Cexif::process_EXIF(unsigned char * CharBuf, unsigned int length)
{
    m_exifinfo->FlashUsed = 0; 
    /* If it's from a digicam, and it used flash, it says so. */
    m_exifinfo->Comments[0] = '\0';  /* Initial value - null string */

    ExifImageWidth = 0;

    {   /* Check the EXIF header component */
        static const unsigned char ExifHeader[] = "Exif\0\0";
        if (memcmp(CharBuf+0, ExifHeader,6)){
			strcpy(m_szLastError,"Incorrect Exif header");
			return 0;
		}
    }

    if (memcmp(CharBuf+6,"II",2) == 0){
        MotorolaOrder = 0;
    }else{
        if (memcmp(CharBuf+6,"MM",2) == 0){
            MotorolaOrder = 1;
        }else{
            strcpy(m_szLastError,"Invalid Exif alignment marker.");
			return 0;
        }
    }

    /* Check the next two values for correctness. */
    if (Get16u(CharBuf+8) != 0x2a){
        strcpy(m_szLastError,"Invalid Exif start (1)");
		return 0;
    }

	int FirstOffset = Get32u(CharBuf+10);
    if (FirstOffset < 8 || FirstOffset > 16){
        // I used to ensure this was set to 8 (website I used indicated its 8)
        // but PENTAX Optio 230 has it set differently, and uses it as offset. (Sept 11 2002)
        strcpy(m_szLastError,"Suspicious offset of first IFD value");
		return 0;
    }

    unsigned char * LastExifRefd = CharBuf;

    /* First directory starts 16 unsigned chars in.  Offsets start at 8 unsigned chars in. */
    if (!ProcessExifDir(CharBuf+14, CharBuf+6, length-6, m_exifinfo, &LastExifRefd))
		return 0;

    /* This is how far the interesting (non thumbnail) part of the exif went. */
    // int ExifSettingsLength = LastExifRefd - CharBuf;

    /* Compute the CCD width, in milimeters. */
    if (m_exifinfo->FocalplaneXRes != 0){
        m_exifinfo->CCDWidth = (float)(ExifImageWidth * m_exifinfo->FocalplaneUnits / m_exifinfo->FocalplaneXRes);
    }

	return 1;
}
//--------------------------------------------------------------------------
// Get 16 bits motorola order (always) for jpeg header stuff.
//--------------------------------------------------------------------------
int Cexif::Get16m(void * Short)
{
    return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 16 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
int Cexif::Get16u(void * Short)
{
    if (MotorolaOrder){
        return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
    }else{
        return (((unsigned char *)Short)[1] << 8) | ((unsigned char *)Short)[0];
    }
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 32 bit signed value from file's native unsigned char order
--------------------------------------------------------------------------*/
long Cexif::Get32s(void * Long)
{
    if (MotorolaOrder){
        return  ((( char *)Long)[0] << 24) | (((unsigned char *)Long)[1] << 16)
              | (((unsigned char *)Long)[2] << 8 ) | (((unsigned char *)Long)[3] << 0 );
    }else{
        return  ((( char *)Long)[3] << 24) | (((unsigned char *)Long)[2] << 16)
              | (((unsigned char *)Long)[1] << 8 ) | (((unsigned char *)Long)[0] << 0 );
    }
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 32 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
unsigned long Cexif::Get32u(void * Long)
{
    return (unsigned long)Get32s(Long) & 0xffffffff;
}
////////////////////////////////////////////////////////////////////////////////

/* Describes format descriptor */
static const int BytesPerFormat[] = {0,1,1,2,4,8,1,1,2,4,8,4,8};
#define NUM_FORMATS 12

#define FMT_BYTE       1 
#define FMT_STRING     2
#define FMT_USHORT     3
#define FMT_ULONG      4
#define FMT_URATIONAL  5
#define FMT_SBYTE      6
#define FMT_UNDEFINED  7
#define FMT_SSHORT     8
#define FMT_SLONG      9
#define FMT_SRATIONAL 10
#define FMT_SINGLE    11
#define FMT_DOUBLE    12

/* Describes tag values */

#define TAG_EXIF_VERSION      0x9000
#define TAG_EXIF_OFFSET       0x8769
#define TAG_INTEROP_OFFSET    0xa005

#define TAG_MAKE              0x010F    //相机DC 制造商
#define TAG_MODEL             0x0110    //DC 型号
#define TAG_ORIENTATION       0x0112    //拍摄时方向，例如向左手旋转DC 90度拍摄照片
#define TAG_XRESOLUTION       0x011A    //X 轴分辨率
#define TAG_YRESOLUTION       0x011B    //Y 轴分辨率
#define TAG_RESOLUTIONUNIT    0x0128    //分辨率单位，例如 inch, cm 
#define TAG_DATATIME          0x0132    //日期时间
#define TAG_YBCR_POSITION     0x0213    //YCbCr 位置控制，例如 居中
#define TAG_COPYRIGHT         0x8298    //版权
#define TAG_EXIF_OFFSET       0x8769    //EXIF 偏移，这时候相当于处理一个新的 EXIF 信息
//#define TAG_GPS_OFFSET		  0x8805	//GPS 偏移，这时候处理GPS信息
#define TAG_GPS2_OFFSET       0x8825	//GPS 偏移
//
#define TAG_IMAGEWIDTH        0x0001    //图像宽度
#define TAG_IMAGEHEIGHT       0x0101    //图像高度
//BOOKMARK
//辅助信息
#define TAG_EXPOSURETIME      0x829A    //曝光时间，例如 1/30 秒
#define TAG_FNUMBER           0x829D    //光圈，例如 F2.8
#define TAG_EXIF_VERSION      0x9000    //EXIF 信息版本
#define TAG_DATETIME_ORIGINAL 0x9003    //照片拍摄时间，例如 2005-10-13 11:09:35
#define TAG_DATATIME_DIGITIZED  0x9004  //相片被其它图像修改软件修改后的时间，例如  2005-10-13 11:36:35
#define TAG_COMPONCONFIG      0x9101    //ComponentsConfiguration 色彩空间配置
#define TAG_COMPRESS_BIT      0x9202    //每像素压缩位数
#define TAG_SHUTTERSPEED      0x9201    //快门速度，例如 1/30 秒
#define TAG_APERTURE          0x9202    //光圈值，例如 F2.8
#define TAG_BRIGHTNESS        0x9203    //亮度
#define TAG_EXPOSURE_BIAS     0x9204    //曝光补偿，例如 EV0.0
#define TAG_MAXAPERTURE       0x9205    //最大光圈值，例如 F2.8
#define TAG_SUBJECT_DISTANCE  0x9206    //拍摄物距离，例如 3.11 米
#define TAG_METERING_MODE     0x9207    //测光模式，例如矩阵
#define TAG_WHITEBALANCE      0x9208    //LightSource 白平衡
#define TAG_FLASH             0x9209    //是否使用闪光灯
#define TAG_FOCALLENGTH       0x920A    //焦距，例如 7.09mm
#define TAG_USERCOMMENT       0x9286    //用户注释
#define TAG_MAKE_COMMENT      0x927C    //厂商注释。这个版本不提供(2005-10-13)
#define TAG_SUBSECTIME        0x9290    //SubSecTime
#define TAG_SUBTIME_ORIGINAL  0x9291    //SubSecTimeOriginal
#define TAG_SUBTIME_DIGITIZED 0x9292    //SubSecTimeDigitized
#define TAG_FLASHPIXVERSION   0x00A0    //Flash Pix 版本
#define TAG_COLORSPACE        0x01A0    //色彩空间，例如 sRGB
#define TAG_PIXEL_XDIMENSION  0x02A0    //
#define TAG_PIXEL_YDIMENSION  0x03A0    //
//#define TAG_

//EXIFR98
//缩略图
#define TAG_INTEROP_OFFSET    0xa005    //偏移
#define TAG_FOCALPLANEXRES    0xA20E    //焦平面X轴分辨率，例如 1024000/278
#define TAG_FOCALPLANEYRES    0xA20F    //焦平面X轴分辨率，例如 768000/209
#define TAG_FOCALPLANEUNITS   0xA210    //焦平面分辨率单位
#define TAG_EXIF_IMAGEWIDTH   0xA002    //EXIF 图像宽度(就是这张 JPG 图像)
#define TAG_EXIF_IMAGELENGTH  0xA003    //EXIF 图像高度
#define TAG_EXPOSURE_PROGRAM  0x8822    //
#define TAG_ISO_EQUIVALENT    0x8827    //
#define TAG_COMPRESSION_LEVEL 0x9102    //
#define TAG_THUMBNAIL_OFFSET  0x0201    //缩略图偏移
#define TAG_THUMBNAIL_LENGTH  0x0202    //缩略图大小

#define TAG_GPS_VERSIONID       0x0000  //GPS 版本
#define TAG_GPS_LATITUDEREF     0x0001  //纬度参考，例如南纬
#define TAG_GPS_LATITUDE        0x0002  //纬度值
#define TAG_GPS_LONGITUDEREF    0x0003  //经度参考，例如东经
#define TAG_GPS_LONGITUDE       0x0004  //经度值
#define TAG_GPS_ALTITUDEREF     0x0005  //海拔高度参考
#define TAG_GPS_ALTITUDE        0x0006  //海拔
#define TAG_GPS_TIMESTAMP       0x0007  //时间戳
#define TAG_GPS_SATELLITES      0x0008  //卫星
#define TAG_GPS_STATUS          0x0009  //状态
#define TAG_GPS_MEASUREMODE     0x000A  //
#define TAG_GPS_DOP             0x000B  //
#define TAG_GPS_SPEEDREF        0x000C  //
#define TAG_GPS_SPEED           0x000D  //
#define TAG_GPS_TRACKREF        0x000E  //
#define TAG_GPS_TRACK           0x000F  //
#define TAG_GPS_IMGDIRECTIONREF 0x0010  //
#define TAG_GPS_IMGDIRECTION    0x0011  //
#define TAG_GPS_MAPDATUM        0x0012  //
#define TAG_GPS_DESTLATITUDEREF 0x0013  //
#define TAG_GPS_DESTLATITUDE    0x0014  //
#define TAG_GPS_DESTLONGITUDEREF  0x0015//
#define TAG_GPS_DESTLONGITUDE   0x0016  //
#define TAG_GPS_DESTBEARINGREF  0x0017  //
#define TAG_GPS_DESTBEARING     0x0018  //
#define TAG_GPS_DESTDISTANCEREF 0x0019  //
#define TAG_GPS_DESTDISTANCE    0x001A  //
/*--------------------------------------------------------------------------
   Process one of the nested EXIF directories.
--------------------------------------------------------------------------*/
bool Cexif::ProcessExifDir(unsigned char * DirStart, unsigned char * OffsetBase, unsigned ExifLength,
                           EXIFINFO * const m_exifinfo, unsigned char ** const LastExifRefdP )
{
    int de;
    int a;
    int NumDirEntries;
    unsigned ThumbnailOffset = 0;
    unsigned ThumbnailSize = 0;

    NumDirEntries = Get16u(DirStart);

    if ((DirStart+2+NumDirEntries*12) > (OffsetBase+ExifLength)){
        strcpy(m_szLastError,"Illegally sized directory");
		return 0;
    }

    for (de=0;de<NumDirEntries;de++){
        int Tag, Format, Components;
        unsigned char * ValuePtr;
            /* This actually can point to a variety of things; it must be
               cast to other types when used.  But we use it as a unsigned char-by-unsigned char
               cursor, so we declare it as a pointer to a generic unsigned char here.
            */
        int BytesCount;
        unsigned char * DirEntry;
        DirEntry = DirStart+2+12*de;

        Tag = Get16u(DirEntry);
        Format = Get16u(DirEntry+2);
        Components = Get32u(DirEntry+4);

        if ((Format-1) >= NUM_FORMATS) {
            /* (-1) catches illegal zero case as unsigned underflows to positive large */
            strcpy(m_szLastError,"Illegal format code in EXIF dir");
			return 0;
		}

        BytesCount = Components * BytesPerFormat[Format];

        if (BytesCount > 4){
            unsigned OffsetVal;
            OffsetVal = Get32u(DirEntry+8);
            /* If its bigger than 4 unsigned chars, the dir entry contains an offset.*/
            if (OffsetVal+BytesCount > ExifLength){
                /* Bogus pointer offset and / or unsigned charcount value */
                strcpy(m_szLastError,"Illegal pointer offset value in EXIF.");
				return 0;
            }
            ValuePtr = OffsetBase+OffsetVal;
        }else{
            /* 4 unsigned chars or less and value is in the dir entry itself */
            ValuePtr = DirEntry+8;
        }

        if (*LastExifRefdP < ValuePtr+BytesCount){
            /* Keep track of last unsigned char in the exif header that was
               actually referenced.  That way, we know where the
               discardable thumbnail data begins.
            */
            *LastExifRefdP = ValuePtr+BytesCount;
        }

        /* Extract useful components of tag */
		printf("%x\n", Tag);
        switch(Tag){

           /* case TAG_MAKE:
                strncpy(m_exifinfo->CameraMake, (char*)ValuePtr, 31);
                break;*/

            case TAG_MODEL:
                strncpy(m_exifinfo->CameraModel, (char*)ValuePtr, 39);
                break;

			case TAG_EXIF_VERSION:
				strncpy(m_exifinfo->Version,(char*)ValuePtr, 4);
				break;

            case TAG_DATETIME_ORIGINAL:
                strncpy(m_exifinfo->DateTime, (char*)ValuePtr, 19);
                break;

            case TAG_USERCOMMENT:
                // Olympus has this padded with trailing spaces. Remove these first. 
                for (a=BytesCount;;){
                    a--;
                    if (((char*)ValuePtr)[a] == ' '){
                        ((char*)ValuePtr)[a] = '\0';
                    }else{
                        break;
                    }
                    if (a == 0) break;
                }

                /* Copy the comment */
                if (memcmp(ValuePtr, "ASCII",5) == 0){
                    for (a=5;a<10;a++){
                        char c;
                        c = ((char*)ValuePtr)[a];
                        if (c != '\0' && c != ' '){
                            strncpy(m_exifinfo->Comments, (char*)ValuePtr+a, 199);
                            break;
                        }
                    }
                    
                }else{
                    strncpy(m_exifinfo->Comments, (char*)ValuePtr, 199);
                }
                break;

            case TAG_FNUMBER:
                /* Simplest way of expressing aperture, so I trust it the most.
                   (overwrite previously computd value if there is one)
                   */
                m_exifinfo->ApertureFNumber = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_APERTURE:
            case TAG_MAXAPERTURE:
                /* More relevant info always comes earlier, so only
                 use this field if we don't have appropriate aperture
                 information yet. 
                */
                if (m_exifinfo->ApertureFNumber == 0){
                    m_exifinfo->ApertureFNumber = (float)exp(ConvertAnyFormat(ValuePtr, Format)*log(2.0)*0.5);
                }
                break;

			case TAG_BRIGHTNESS:
				m_exifinfo->Brightness = (float)ConvertAnyFormat(ValuePtr, Format);
				break;

            case TAG_FOCALLENGTH:
                /* Nice digital cameras actually save the focal length
                   as a function of how farthey are zoomed in. 
                */

                m_exifinfo->FocalLength = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_SUBJECT_DISTANCE:
                /* Inidcates the distacne the autofocus camera is focused to.
                   Tends to be less accurate as distance increases.
                */
                m_exifinfo->Distance = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_EXPOSURETIME:
                /* Simplest way of expressing exposure time, so I
                   trust it most.  (overwrite previously computd value
                   if there is one) 
                */
                m_exifinfo->ExposureTime = 
                    (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_SHUTTERSPEED:
                /* More complicated way of expressing exposure time,
                   so only use this value if we don't already have it
                   from somewhere else.  
                */
                if (m_exifinfo->ExposureTime == 0){
                    m_exifinfo->ExposureTime = (float)
                        (1/exp(ConvertAnyFormat(ValuePtr, Format)*log(2.0)));
                }
                break;

            case TAG_FLASH:
                if ((int)ConvertAnyFormat(ValuePtr, Format) & 7){
                    m_exifinfo->FlashUsed = 1;
                }else{
                    m_exifinfo->FlashUsed = 0;
                }
                break;

            case TAG_ORIENTATION:
                m_exifinfo->Orientation = (int)ConvertAnyFormat(ValuePtr, Format);
                if (m_exifinfo->Orientation < 1 || m_exifinfo->Orientation > 8){
                    strcpy(m_szLastError,"Undefined rotation value");
                    m_exifinfo->Orientation = 0;
                }
                break;

            case TAG_EXIF_IMAGELENGTH:
            case TAG_EXIF_IMAGEWIDTH:
                /* Use largest of height and width to deal with images
                   that have been rotated to portrait format.  
                */
                a = (int)ConvertAnyFormat(ValuePtr, Format);
                if (ExifImageWidth < a) ExifImageWidth = a;
                break;

            case TAG_FOCALPLANEXRES:
                m_exifinfo->FocalplaneXRes = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_FOCALPLANEYRES:
                m_exifinfo->FocalplaneYRes = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

			case TAG_RESOLUTIONUNIT:
                switch((int)ConvertAnyFormat(ValuePtr, Format)){
                    case 1: m_exifinfo->ResolutionUnit = 1.0f; break; /* 1 inch */
                    case 2:	m_exifinfo->ResolutionUnit = 1.0f; break;
                    case 3: m_exifinfo->ResolutionUnit = 0.3937007874f;    break;  /* 1 centimeter*/
                    case 4: m_exifinfo->ResolutionUnit = 0.03937007874f;   break;  /* 1 millimeter*/
                    case 5: m_exifinfo->ResolutionUnit = 0.00003937007874f;  /* 1 micrometer*/
                }
                break;

            case TAG_FOCALPLANEUNITS:
                switch((int)ConvertAnyFormat(ValuePtr, Format)){
                    case 1: m_exifinfo->FocalplaneUnits = 1.0f; break; /* 1 inch */
                    case 2:	m_exifinfo->FocalplaneUnits = 1.0f; break;
                    case 3: m_exifinfo->FocalplaneUnits = 0.3937007874f;    break;  /* 1 centimeter*/
                    case 4: m_exifinfo->FocalplaneUnits = 0.03937007874f;   break;  /* 1 millimeter*/
                    case 5: m_exifinfo->FocalplaneUnits = 0.00003937007874f;  /* 1 micrometer*/
                }
                break;

                // Remaining cases contributed by: Volker C. Schoech <schoech(at)gmx(dot)de>

            case TAG_EXPOSURE_BIAS:
                m_exifinfo->ExposureBias = (float) ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_WHITEBALANCE:
                m_exifinfo->Whitebalance = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_METERING_MODE:
                m_exifinfo->MeteringMode = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_EXPOSURE_PROGRAM:
                m_exifinfo->ExposureProgram = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_ISO_EQUIVALENT:
                m_exifinfo->ISOequivalent = (int)ConvertAnyFormat(ValuePtr, Format);
                if ( m_exifinfo->ISOequivalent < 50 ) m_exifinfo->ISOequivalent *= 200;
                break;

            case TAG_COMPRESSION_LEVEL:
                m_exifinfo->CompressionLevel = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_XRESOLUTION:
                m_exifinfo->Xresolution = (float)ConvertAnyFormat(ValuePtr, Format);
                break;
            case TAG_YRESOLUTION:
                m_exifinfo->Yresolution = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_THUMBNAIL_OFFSET:
                ThumbnailOffset = (unsigned)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_THUMBNAIL_LENGTH:
                ThumbnailSize = (unsigned)ConvertAnyFormat(ValuePtr, Format);
                break;

			case TAG_GPS_VERSIONID:
				break;
			case TAG_GPS_LATITUDEREF:
				strncpy(m_exifinfo->LatitudeRef,(char*)ValuePtr, 4);
				break;
			case TAG_GPS_LATITUDE:
				{
				//	int nIndex;
					float fDuLatitude = (float)ConvertAnyFormat(ValuePtr, Format);
				//					nIndex = sprintf(m_exifinfo->Latitude, "%.0f", fDuLatitude);
					
					float fFenLatitude = (float)ConvertAnyFormat(ValuePtr+8, Format);
				//					nIndex += sprintf(m_exifinfo->Latitude + nIndex, " %.0f", fFenLatitude);
					
					float fMiaoLatitude = (float)ConvertAnyFormat(ValuePtr+16, Format);
				//					sprintf(m_exifinfo->Latitude + nIndex, "\' %f", fMiaoLatitude);
					
					m_exifinfo->Latitude = fDuLatitude + fFenLatitude/60.0 + fMiaoLatitude/3600.0;
					break;
				}
			case TAG_GPS_LONGITUDEREF:
				strncpy(m_exifinfo->LongitudeRef,(char*)ValuePtr, 4);
				break;
			case TAG_GPS_LONGITUDE:
				{
			//		int nIndex;
					float fDuLongitude = (float)ConvertAnyFormat(ValuePtr, Format);
	//						nIndex = sprintf(m_exifinfo->Longitude, "%.0f", fDuLongitude);
					
					float fFenLongitude = (float)ConvertAnyFormat(ValuePtr+8, Format);
	//								nIndex += sprintf(m_exifinfo->Longitude + nIndex, " %.0f", fFenLongitude);
					
					float fMiaoLongitude = (float)ConvertAnyFormat(ValuePtr+16, Format);
	//								sprintf(m_exifinfo->Longitude + nIndex, "\' %f", fMiaoLongitude);
					
					m_exifinfo->Longitude = fDuLongitude + fFenLongitude/60.0 + fMiaoLongitude/3600.0;
					break;
				}
			case TAG_GPS_ALTITUDEREF:
				strncpy(m_exifinfo->AltitudeRef,(char*)ValuePtr, 15);
				break;
			case TAG_GPS_ALTITUDE:
				m_exifinfo->Altitude = (float)ConvertAnyFormat(ValuePtr, Format);
				break;
			case TAG_GPS_TIMESTAMP:
				strncpy(m_exifinfo->TimeStamp,(char*)ValuePtr, 15);
				break;			
			case TAG_GPS_DESTLATITUDEREF:
				float ff = (float)ConvertAnyFormat(ValuePtr, Format);
				break;
        }

        if (Tag == TAG_EXIF_OFFSET || Tag == TAG_INTEROP_OFFSET  || Tag == TAG_GPS2_OFFSET){
            unsigned char * SubdirStart;
            SubdirStart = OffsetBase + Get32u(ValuePtr);
            if (SubdirStart < OffsetBase || 
                SubdirStart > OffsetBase+ExifLength){
                strcpy(m_szLastError,"Illegal subdirectory link");
				return 0;
            }
            ProcessExifDir(SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
            continue;
        }
    }


    {
        /* In addition to linking to subdirectories via exif tags,
           there's also a potential link to another directory at the end
           of each directory.  This has got to be the result of a
           committee!  
        */
        unsigned char * SubdirStart;
        unsigned Offset;
        Offset = Get16u(DirStart+2+12*NumDirEntries);
        if (Offset){
            SubdirStart = OffsetBase + Offset;
            if (SubdirStart < OffsetBase 
                || SubdirStart > OffsetBase+ExifLength){
                strcpy(m_szLastError,"Illegal subdirectory link");
				return 0;
            }
            ProcessExifDir(SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
        }
    }


    if (ThumbnailSize && ThumbnailOffset){
        if (ThumbnailSize + ThumbnailOffset <= ExifLength){
            /* The thumbnail pointer appears to be valid.  Store it. */
            m_exifinfo->ThumbnailPointer = OffsetBase + ThumbnailOffset;
            m_exifinfo->ThumbnailSize = ThumbnailSize;
        }
    }

	return 1;
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Evaluate number, be it int, rational, or float from directory.
--------------------------------------------------------------------------*/
double Cexif::ConvertAnyFormat(void * ValuePtr, int Format)
{
    double Value;
    Value = 0;

    switch(Format){
        case FMT_SBYTE:     Value = *(signed char *)ValuePtr;  break;
        case FMT_BYTE:      Value = *(unsigned char *)ValuePtr;        break;

        case FMT_USHORT:    Value = Get16u(ValuePtr);          break;
        case FMT_ULONG:     Value = Get32u(ValuePtr);          break;

        case FMT_URATIONAL:
        case FMT_SRATIONAL: 
            {
                int Num,Den;
                Num = Get32s(ValuePtr);
                Den = Get32s(4+(char *)ValuePtr);
                if (Den == 0){
                    Value = 0;
                }else{
                    Value = (double)Num/Den;
                }
                break;
            }

        case FMT_SSHORT:    Value = (signed short)Get16u(ValuePtr);  break;
        case FMT_SLONG:     Value = Get32s(ValuePtr);                break;

        /* Not sure if this is correct (never seen float used in Exif format)
         */
        case FMT_SINGLE:    Value = (double)*(float *)ValuePtr;      break;
        case FMT_DOUBLE:    Value = *(double *)ValuePtr;             break;
    }
    return Value;
}
////////////////////////////////////////////////////////////////////////////////
void Cexif::process_COM (const unsigned char * Data, int length)
{
    int ch;
    char Comment[MAX_COMMENT+1];
    int nch;
    int a;

    nch = 0;

    if (length > MAX_COMMENT) length = MAX_COMMENT; // Truncate if it won't fit in our structure.

    for (a=2;a<length;a++){
        ch = Data[a];

        if (ch == '\r' && Data[a+1] == '\n') continue; // Remove cr followed by lf.

        if ((ch>=0x20) || ch == '\n' || ch == '\t'){
            Comment[nch++] = (char)ch;
        }else{
            Comment[nch++] = '?';
        }
    }

    Comment[nch] = '\0'; // Null terminate

    //if (ShowTags) printf("COM marker comment: %s\n",Comment);

    strcpy(m_exifinfo->Comments,Comment);
}
////////////////////////////////////////////////////////////////////////////////
void Cexif::process_SOFn (const unsigned char * Data, int marker)
{
    int data_precision, num_components;

    data_precision = Data[2];
    m_exifinfo->Height = Get16m((void*)(Data+3));
    m_exifinfo->Width = Get16m((void*)(Data+5));
    num_components = Data[7];

    if (num_components == 3){
        m_exifinfo->IsColor = 1;
    }else{
        m_exifinfo->IsColor = 0;
    }

    m_exifinfo->Process = marker;

    //if (ShowTags) printf("JPEG image is %uw * %uh, %d color components, %d bits per sample\n",
    //               ImageInfo.Width, ImageInfo.Height, num_components, data_precision);
}
////////////////////////////////////////////////////////////////////////////////

