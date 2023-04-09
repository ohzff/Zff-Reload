#ifndef ZFFVER
#define ZFFVER

#define ZFFVERSION "DEV"

void version_output ()
{
    printf ("Zff Version 6.0 Beta\nMade by ohzff 5+1 <https://github.com/ohzff/Zff-Reload>.\n");
    printf ("\nEnvironment information:\n");
    printf ("Zff version              %s\n", ZFFVERSION);
    printf ("Data path                %susr\n", DATAPATH);
}

#endif