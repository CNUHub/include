#ifndef __cnudicom_h
#define __cnudicom_h

#include "psyhdr.h"

enum show_mode { TERSE=-3, CONCISE, BRIEF, NORMAL, LENGTHY, VERBOSE, TEDIOUS };

class DICOM_VR {
 private:
  int vr;
  string name;
  psytype type;
 public:
  DICOM_VR(int vr, string name, psytype type) {
    DICOM_VR::vr = vr;
    DICOM_VR::name = name;
    DICOM_VR::type = type;
  }
  ~DICOM_VR() { }
  int getVR() { return vr; }
  psytype getType() { return type; }
  void show(ostream *out= &cout);
};
DICOM_VR* getDICOM_VR(int vr);

class DICOM_Tag {
 private:
  int groupNelement;
  DICOM_VR* vr;
  string name;
  int knownTag;
 public:
  DICOM_Tag(int groupNelement, DICOM_VR* vr, string name) {
    DICOM_Tag::groupNelement = groupNelement;
    DICOM_Tag::vr = vr;
    DICOM_Tag::name = name;
    knownTag = 0;
  }
  virtual ~DICOM_Tag() { }
  int getCombinedGroupAndElement() { return groupNelement; }
  DICOM_VR* getImplicitVR() { return vr; }
  void show(ostream *out= &cout, show_mode showMode=NORMAL);
};
DICOM_Tag* getDICOM_Tag(int group, int element);
DICOM_Tag* getDICOM_Tag(int groupNelement);

enum vrMode { UNKNOWN_VR_MODE=0, IMPLICIT_VR, EXPLICIT_VR };
/*
static char* vrModeNames[] = {
  "UNKNOWN_VR_MODE", "IMPLICIT_VR", "EXPLICIT_VR" };
*/

extern char* vrModeNames[];

class DICOM_DataElement {
 public:
  DICOM_DataElement *link;
  DICOM_Tag* tag;
  DICOM_VR* vr;
  vrMode mode;
  psytype storageType;
  long fileOffset;
  long dataFileOffset;
  int dataLength;
  char* data;
  DICOM_DataElement() {
    link = NULL;
    tag = NULL; vr = NULL; mode = UNKNOWN_VR_MODE;
    storageType = psynotype;
    fileOffset = 0;
    dataFileOffset = 0;
    dataLength = 0;
    data = NULL;
  }
  void show(ostream *out= &cout, show_mode showMode=NORMAL);
};

DICOM_DataElement *getDICOM_DataElement(fstream *fd, vrMode mode,
					psyswaptype swap);

void writeDICOM_DataElementHeader(DICOM_DataElement *dde, fstream *fd,
				  psyswaptype swap);

void writeDICOM_DataElementData(DICOM_DataElement *dde, unsigned char *dataptr,
				fstream *fd, psyswaptype swap);

psytype getdicomclosesttype(psytype type);

int isdicomfile(string name);

class dicomfile : public rawfile {
 protected:
  DICOM_DataElement *firstDataElement;
  DICOM_DataElement *lastDataElement;
  psyimg *combinedFileSetPtr;
 public:
  dicomfile(string fname, const char *mode=NULL);
  dicomfile(string fname, psyimg *psyimgptr, psytype pixeltype=psynotype);
  void copyblock(char *outbuff, int xorig, int yorig, int zorig,
		 int iorig, int xend, int yend, int zend, int iend,
		 int xinc, int yinc, int zinc, int iinc,
		 psytype pixeltype);
  void initgetpixel(psytype pixeltype, int x, int y, int z, int i);
  void getpixel(char *pixel, psytype pixeltype,
		int x, int y, int z, int i);
  void getnextpixel(char *pixel);
  void output_tree(ostream *out) {rawfile::output_tree(out);*out<<"::dicomfile";};
  void showhdr(ostream *out= &cout, show_mode showMode=NORMAL);
};

extern DICOM_VR AE;
extern DICOM_VR AS;
extern DICOM_VR AT;
extern DICOM_VR CS;
extern DICOM_VR DA;
extern DICOM_VR DS;
extern DICOM_VR DT;
extern DICOM_VR FL;
extern DICOM_VR FD;
extern DICOM_VR IS;
extern DICOM_VR LO;
extern DICOM_VR LT;
extern DICOM_VR OB;
extern DICOM_VR OW;
extern DICOM_VR PN;
extern DICOM_VR SH;
extern DICOM_VR SL;
extern DICOM_VR SQ;
extern DICOM_VR SS;
extern DICOM_VR ST;
extern DICOM_VR TM;
extern DICOM_VR UI;
extern DICOM_VR UL;
extern DICOM_VR UN;
extern DICOM_VR US;
extern DICOM_VR UT;
extern DICOM_VR QQ;
extern DICOM_VR* vr_list[];


/*
static DICOM_VR AE(0x4145, "Application Entity", psystring);//16 bytes max
static DICOM_VR AS(0x4153, "Age String", psystring);//4 bytes fixed
static DICOM_VR AT(0x4154, "Attribute Tag", psyushort);
static DICOM_VR CS(0x4353, "Code String", psystring);
static DICOM_VR DA(0x4441, "Date", psystring);
static DICOM_VR DS(0x4453, "Decimal String", psystring);
static DICOM_VR DT(0x4454, "Date Time", psystring);
static DICOM_VR FL(0x464C, "Floating Point Single", psyfloat);
static DICOM_VR FD(0x4644, "Floating Point Double", psydouble);
static DICOM_VR IS(0x4953, "Integer String", psystring); //12 bytes max
static DICOM_VR LO(0x4C4F, "Long String", psystring); //64 chars max
static DICOM_VR LT(0x4C54, "Long Text", psystring);//10240 chars max
static DICOM_VR OB(0x4F42, "Other Byte String", psychar);
static DICOM_VR OW(0x4F57, "Other Word String", psyshort);
static DICOM_VR PN(0x504E, "Person Name", psystring);//5 groups X 64max
static DICOM_VR SH(0x5348, "Short String", psystring);//16 chars max
static DICOM_VR SL(0x534C, "Signed Long", psyint);
static DICOM_VR SQ(0x5351, "Value Sequence", psydicomdataelement);
static DICOM_VR SS(0x5353, "Signed Short", psyshort);
static DICOM_VR ST(0x5354, "Short Text", psystring);//1024 chars max
static DICOM_VR TM(0x544D, "Time", psystring);//16 bytes max
static DICOM_VR UI(0x5549, "Unique Identifier", psystring);//64 bytes max
static DICOM_VR UL(0x554C, "Unsigned Long", psyuint);
static DICOM_VR UN(0x554E, "Unknown", psychar);
static DICOM_VR US(0x5553, "Unsigned Short", psyushort);
static DICOM_VR UT(0x5554, "Unlimited Text", psystring);
static DICOM_VR QQ(0x3F3F, "", psynotype);
static DICOM_VR* vr_list[] = {
  &AE, &AS, &AT, &CS, &DA, &DS, &DT, &FD, &FL, &IS, &LO, &LT, &PN,
  &SH, &SL, &SS, &ST, &TM, &UI, &UL, &US, &UT, &OB, &OW, &SQ, &UN,
  &QQ, NULL
};
*/
#endif /* !__cnudicom_h */
