/////////////////////////////////////////////////////////////////////
//                        Ӱ��������ƽ̨                         //
//                                                                 //
// ��  �ܣ��ṩӰ�����Ļ������ܡ�                                //
//                                                                 //
// ��  Ȩ����Ȩ���� 2007~2010 ��Ծ                                 //
//=================================================================//


#ifndef	_IMAGE_H_
#define _IMAGE_H_


#include <stdio.h>
#include <stdlib.h>
#include "WINDOWS.H"


#ifdef _WINDOWS_
#define EXPORT_C                    __declspec(dllexport)
#endif

#ifdef __WINDOWS__
#define EXPORT_C                    __declspec(dllexport)
#endif


#pragma warning(disable : 4103)
#pragma warning(disable : 4251)
#pragma warning(disable : 4273)
#pragma warning(disable : 4996)


/////////////////////////////////////////////////////////////////////
//                             �궨��                              //
//=================================================================//
// �汾��Ϣ
#define VERSION                     0x01000000 // 1.0.0.0

// Ӱ����Գߴ�
#define IMAGE_WIDTH(pimage)         ((int)((pimage)->bmpInfo->bmiHeader.biWidth))
#define IMAGE_HEIGHT(pimage)        ((int)((pimage)->bmpInfo->bmiHeader.biHeight))

// ��������ߴ�
#define IMAGE_AREA_WIDTH(pimage)    ((int)((pimage)->ex - (pimage)->sx + 1))
#define IMAGE_AREA_HEIGHT(pimage)   ((int)((pimage)->ey - (pimage)->sy + 1))

// Ӱ��ɫ��
#define IMAGE_BITCOUNT(pimage)      ((int)((pimage)->bmpInfo->bmiHeader.biBitCount))

// ��� RGB
#define RGB(r,g,b)                  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define RGBA(r,g,b,a)               ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)(BYTE)(a))<<24))
#define RGB565_RGB(r,g,b)           ((COLORREF)((((r >> 3) & 0x1F) << 11) | (((g >> 2) & 0x3F) << 5) | (((b >> 3) & 0x1F))))

// �ֽ� RGB
#define RGB565_GET_R(color)         (BYTE)((((color) >> 11) & 0x1F) << 3)
#define RGB565_GET_G(color)         (BYTE)((((color) >> 5)  & 0x3F) << 2)
#define RGB565_GET_B(color)         (BYTE)((((color) >> 0)  & 0x1F) << 3)

#define GET_RED(color)              (BYTE)((color)  &  0xff)
#define GET_GRN(color)              (BYTE)(((color) >> 0x08) & 0xff)
#define GET_BLU(color)              (BYTE)(((color) >> 0x10) & 0xff)
#define GET_ALP(color)              (BYTE)(((color) >> 0x18) & 0xff)
//===================================================================


/////////////////////////////////////////////////////////////////////
//                            ���󷵻�ֵ                           //
//=================================================================//
#ifndef _ERROR_H_

// ���д�����Ϣ (-50 ~ 0)
#define ERR_MEM                     -1 // ����洢ʧ��
#define ERR_IMAGE                   -2 // Ӱ����Ч
#define ERR_RANGE                   -3 // �������򳬳�Ӱ��ߴ�
#define ERR_BITCOUNT                -4 // Ӱ��ɫ�����Ҫ��
#define ERR_PARAMETER               -5 // ��������
#define ERR_LIST                    -6 // �������
#define ERR_MATRIX                  -7 // �������

// I/O ������Ϣ (-100 ~ -51)
#define ERR_IO_SEEK                 -51 // Ӱ���ļ���λ����
#define ERR_IO_FORMAT               -52 // Ӱ���ļ���ʽ����
#define ERR_IO_OPENFILE             -53 // ��Ӱ���ļ�ʧ��
#define ERR_IO_BITCOUNT             -54 // Ӱ���ļ���Ӱ��ɫ�����Ҫ��
#define ERR_IO_COMPRESS             -55 // Ӱ��ʹ��ѹ����ʽ
#define ERR_IO_READDATA             -56 // ��ȡӰ���ļ�����ʧ��
#define ERR_IO_WRITEDATA            -57 // д��Ӱ���ļ�����ʧ��

#endif
//===================================================================


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////////
//                          ��׼Ӱ��ͷ����                         //
//=================================================================//
typedef struct {
	unsigned long   sx, ex;    // ��������Χ
	unsigned long   sy, ey;    // ��������Χ
	unsigned long   buffWidth; // �л���������
	unsigned char  *data;      // Ӱ�����ݻ��� Image Data Buffer
	unsigned char **matrix;    // Ӱ�����ݾ��� Image Data Matrix
	BITMAPINFO     *bmpInfo;   // Ӱ���ļ���Ϣ
} IMAGE;
//===================================================================


/////////////////////////////////////////////////////////////////////
//                         ��ɫϵͳ�ṹ����                        //
//=================================================================//
// GRAY
typedef unsigned char IMGGRAY;

// RGB
typedef struct {
	unsigned char B;  // ��
	unsigned char G;  // ��
	unsigned char R;  // ��
} IMGRGB;

// RGBA
typedef struct {
	unsigned char B;  // ��
	unsigned char G;  // ��
	unsigned char R;  // ��
	unsigned char A;  // ͸��
} IMGRGBA;

// YIQ��ɫϵͳͨ���������ĵ���ϵͳ�����ã�����NTSCϵͳ��
typedef struct {
	float         Y;  // ����
	float         I;  // ɫ��
	float         Q;  // ���Ͷ�
} YIQ;

// YUV��ɫϵͳ��ŷ�޵ĵ���ϵͳ���ã�����PALϵͳ��
typedef struct {
	float         Y;  // ����
	float         U;  // ɫ��
	float         V;  // ���Ͷ�
} YUV;

// YCbCr�Ǵ�YUVɫ��ϵͳ�����������ģ�JPEG���õ�ɫ��ϵͳ���Ǹ�ϵͳ
typedef struct {
	float         Y;  // ����
	float         Cb; // ɫ��
	float         Cr; // ���Ͷ�
} YCbCr;
//===================================================================


/////////////////////////////////////////////////////////////////////
//                             ���ĺ���                            //
//=================================================================//
// ����Ϣ����
EXPORT_C void IMAGE_GetLibraryInfo(char * const pszinfo);
EXPORT_C unsigned long IMAGE_GetVersion(void);


// ����洢
EXPORT_C void** IMAGE_AllocMatrix(int const nrows, int const ncols, int const nsize);
EXPORT_C void IMAGE_FreeMatrix(void ** const pmatrix);
EXPORT_C int IMAGE_CopyMatrix(void ** const pmtxsrc, void ** const pmtxdst, int const nrows, int const ncols, int const nsize);


// Ӱ��洢
EXPORT_C void IMAGE_ZeroImage(IMAGE * const pimage);
EXPORT_C void IMAGE_FreeImage(IMAGE * const pimage);
EXPORT_C int IMAGE_AllocImage(IMAGE * const pimage, int const nwidth, int const nheight, int const nbitcount);

EXPORT_C int IMAGE_CopyImage(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_CopyImageArea(IMAGE * const pimgsrc, IMAGE * const pimgdst);


// ����/�ָ�����������
EXPORT_C void IMAGE_SetImageArea(IMAGE * const pimage, int const sx, int const sy, int const ex, int const ey);
EXPORT_C void IMAGE_ResetImageArea(IMAGE * const pimage);


// ���ز�������
EXPORT_C unsigned long IMAGE_GetPixelColor(IMAGE * const pimage, int const x, int const y);
EXPORT_C void IMAGE_SetPixelColor(IMAGE * const pimage, int const x, int const y, unsigned long const color);


// ɫ��ת������
EXPORT_C int IMAGE_Convert1BitTo8Bit(IMAGE * const pimg1bitsrc, IMAGE * const pimg8bitdst);
EXPORT_C int IMAGE_Convert8BitTo24Bit(IMAGE * const pimg8bitsrc, IMAGE * const pimg24bitdst);


// �Ҷ�ת������
#define GRAY_STD 0 // ���ձ�׼�Ҷȷ�ʽ
#define GRAY_RED 1 // ���պ�ɫͨ����ʽ
#define GRAY_GRN 2 // ������ɫͨ����ʽ
#define GRAY_BLU 3 // ������ɫͨ����ʽ
EXPORT_C int IMAGE_ColorToGray(IMAGE * const pimg24bitsrc, IMAGE * const pimg8bitdst, int const nflag);


// �������㺯��
EXPORT_C int IMAGE_FlipImage(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_MirrorImage(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_Resize(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_ResizeEx(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_Rotate(IMAGE * const pimgsrc, IMAGE * const pimgdst, float const fradian);
EXPORT_C int IMAGE_RotateEx(IMAGE * const pimgsrc, IMAGE * const pimgdst, float const fradian);


// ��ɫϵͳ�任
EXPORT_C int IMAGE_RGB2YIQ(IMAGE * const prgbsrc, YIQ ** const pyiqdst);
EXPORT_C int IMAGE_YIQ2RGB(YIQ ** const pyiqsrc, IMAGE * const prgbdst);

EXPORT_C int IMAGE_RGB2YUV(IMAGE * const prgbsrc, YUV ** const pyuvdst);
EXPORT_C int IMAGE_YUV2RGB(YUV ** const pyuvsrc, IMAGE * const prgbdst);

EXPORT_C int IMAGE_RGB2YCbCr(IMAGE * const prgbsrc, YCbCr ** const pycbcrdst);
EXPORT_C int IMAGE_YCbCr2RGB(YCbCr ** const pycbcrsrc, IMAGE * const prgbdst);


// I/O����
EXPORT_C int IMAGE_LoadImage(char * const pszfilename, IMAGE * const pimage);

EXPORT_C int IMAGE_LoadBmpHeader(char * const pszfilename, BITMAPINFOHEADER * const pbmpinfoheader);
EXPORT_C int IMAGE_LoadBmp(char * const pszfilename, IMAGE * const pimage);
EXPORT_C int IMAGE_SaveBmp(char * const pszfilename, IMAGE * const pimage);

EXPORT_C int IMAGE_LoadJpgHeader(char * const pszfilename, BITMAPINFOHEADER * const pbmpinfoheader);
EXPORT_C int IMAGE_LoadJpg(char * const pszfilename, IMAGE * const pimage);
EXPORT_C int IMAGE_SaveJpg(char * const pszfilename, IMAGE * const pimage, int const nquality);

EXPORT_C int IMAGE_LoadPngHeader(char * const pszfilename, BITMAPINFOHEADER * const pbmpinfoheader);
EXPORT_C int IMAGE_LoadPng(char * const pszfilename, IMAGE * const pimage);
EXPORT_C int IMAGE_SavePng(char * const pszfilename, IMAGE * const pimage);


EXPORT_C int IMAGE_LoadImageEx(FILE * const pfile, IMAGE * const pimage);

EXPORT_C int IMAGE_LoadBmpHeaderEx(FILE * const pfile, BITMAPINFOHEADER * const pbmpinfoheader);
EXPORT_C int IMAGE_LoadBmpEx(FILE * const pfile, IMAGE * const pimage);
EXPORT_C int IMAGE_SaveBmpEx(FILE * const pfile, IMAGE * const pimage);

// ע�⣺IMAGE_LoadJpgEx����ر�ʵ����Ҫ������ֽڣ������ᵼ��FILE��λ��ǰ����ʹ��ʱ�ɽ�
//       Jpeg�ļ��������ļ����������ļ�����ϸ��¼��¼��������������ļ���ʼ��ƫ����
EXPORT_C int IMAGE_LoadJpgHeaderEx(FILE * const pfile, BITMAPINFOHEADER * const pbmpinfoheader);
EXPORT_C int IMAGE_LoadJpgEx(FILE * const pfile, IMAGE * const pimage);
EXPORT_C int IMAGE_SaveJpgEx(FILE * const pfile, IMAGE * const pimage, int const nquality);

EXPORT_C int IMAGE_LoadPngHeaderEx(FILE * const pfile, BITMAPINFOHEADER * const pbmpinfoheader);
EXPORT_C int IMAGE_LoadPngEx(FILE * const pfile, IMAGE * const pimage);
EXPORT_C int IMAGE_SavePngEx(FILE * const pfile, IMAGE * const pimage);
//===================================================================


/////////////////////////////////////////////////////////////////////
//                             ���ܺ���                            //
//=================================================================//
EXPORT_C int IMAGE_ChangeBright(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const namount);
EXPORT_C int IMAGE_ChangeBrightEx(IMAGE * const pimgsrc, IMAGE * const pimgdst, float const famount);

EXPORT_C int IMAGE_Multiply(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const nmultiply);
EXPORT_C int IMAGE_Divide(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const ndivide);

EXPORT_C int IMAGE_ExpandContrast(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const nlower, int const nupper);
EXPORT_C int IMAGE_GammaBrighten(IMAGE * const pimgsrc, IMAGE * const pimgdst, float const fgamma);

EXPORT_C int IMAGE_CalcHisto(IMAGE * const pimage, unsigned long * const redtab, unsigned long * const grntab, unsigned long * const blutab);
EXPORT_C int IMAGE_Histoequalize(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_Negative(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_BlackWhite(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const nthresh);



EXPORT_C int IMAGE_Blur(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_GaussBlur(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_GaussBlurEx(IMAGE * const pimgsrc, IMAGE * const pimgdst, float const sigma);

EXPORT_C int IMAGE_Sharpen(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_SharpenGentle(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_SharpenLaplace(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_Outline(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_MedianFilter(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const nsize);
EXPORT_C int IMAGE_RemoveNoise(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_MatrixConvert(IMAGE * const pimgsrc, IMAGE * const pimgdst, char * const kernel);
EXPORT_C int IMAGE_MatrixConvertEx(IMAGE * const pimgsrc, IMAGE * const pimgdst, char * const kernel, int const nsize, int const ndivide);



EXPORT_C int IMAGE_Dilate(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const namount);
EXPORT_C int IMAGE_Erode(IMAGE * const pimgsrc, IMAGE * const pimgdst, int const namount);

EXPORT_C int IMAGE_DilationH(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_DilationV(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_DilationBlock(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_ErosionH(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_ErosionV(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_ErosionBlock(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_OpenH(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_OpenV(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_OpenBlock(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_CloseH(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_CloseV(IMAGE * const pimgsrc, IMAGE * const pimgdst);
EXPORT_C int IMAGE_CloseBlock(IMAGE * const pimgsrc, IMAGE * const pimgdst);

EXPORT_C int IMAGE_Thinning(IMAGE * const pimgsrc, IMAGE * const pimgdst);



// ����
typedef struct {
	double re; // ʵ��
	double im; // �鲿
} COMPLEX;

EXPORT_C int IMAGE_DFT(IMAGE * const pimgsrc, COMPLEX ** const ppdata, int const powerwidth, int const powerheight);
EXPORT_C int IMAGE_IDFT(COMPLEX ** const ppdata, IMAGE * const pimgdst, int const powerwidth, int const powerheight);

EXPORT_C int IMAGE_DCT(IMAGE * const pimgsrc, float ** const ppdata, int const powerwidth, int const powerheight);
EXPORT_C int IMAGE_IDCT(float ** const ppdata, IMAGE * const pimgdst, int const powerwidth, int const powerheight);

EXPORT_C int IMAGE_DWT(IMAGE * const pimgsrc, float ** const ppdata, int const levs, BOOL const bpacket, char const cparam, int const nparam);
EXPORT_C int IMAGE_IDWT(float ** const ppdata, IMAGE * const pimgdst, int const levs, BOOL const bpacket, char const cparam, int const nparam);
//===================================================================



#ifdef __cplusplus
}
#endif

#endif