#ifndef _CPUID_H_
#define _CPUID_H_

char *cpuVendor(char *buffer);
char *cpuModel(int dir,char *buffer);
int isCpuModelPresent();

#endif