#ifndef __psyiofunctions_h
#define __psyiofunctions_h
struct unitpair {
  string name;
  double factor;
};

class unitinput {
  unitpair *unitlist;
  double defaultvalue;
  string defaultunits;
 public:
  unitinput();
  unitinput(string type);
  ~unitinput();
  void initunitinput();
  void initunitinput(string type);
  void setdefaultunits(string name);
  string getdefaultunits();
  void setdefaultvalue(double value);
  double getdefaultvalue();
  void setpixelunits(double factor);
  double get(string prompt, istream *instream=&cin);
  double sget(char *str, int *status=NULL);
};

string *read_list(const char *name, int *numberoffiles);
void free_read_list(string *ptr);

#endif
