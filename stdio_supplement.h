#ifndef __stdio_supplement_h
#define __stdio_supplement_h

#ifdef NEED_STDIO_SUPPLEMENT
extern int printf(const char *format, ...);
extern int fprintf(FILE *stream, const char *format, ...);
extern int fscanf(FILE *stream, const char *format, ...);
extern int sscanf(const char *s, const char *format, ...);
extern int fclose(FILE *stream);
extern void rewind(FILE *stream);
extern char toupper(char c);
#endif

#endif
