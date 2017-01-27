  switch (intype) {
  case psychar:
    {
      char *inptr=(char *)in;
      *outptr = *inptr;
    }
    break;
  case psyuchar:
    {
      unsigned char *inptr=(unsigned char *)in;
      *outptr = *inptr;
    }
    break;
  case psyshort:
    {
      short *inptr=(short *)in;
      *outptr = *inptr;
    }
    break;
  case psyushort:
    {
      unsigned short *inptr=(unsigned short *)in;
      *outptr = *inptr;
    }
    break;
  case psyint:
    {
      int *inptr=(int *)in;
      *outptr = *inptr;
    }
    break;
#ifdef conversionswitchint
  case psyfloat:
    {
      float *inptr=(float *)in;
      *outptr = irint(*inptr);
    }
    break;
  case psydouble:
    {
      double *inptr=(double *)in;
      *outptr = irint(*inptr);
    }
    break;
#else
  case psyfloat:
    {
      float *inptr=(float *)in;
      *outptr = *inptr;
    }
    break;
  case psydouble:
    {
      double *inptr=(double *)in;
      *outptr = *inptr;
    }
    break;
#endif
  default:
    cerr<<"type2* - unemplimented output type\n";
    exit(1);
  }
