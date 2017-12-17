#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *openFile(FILE *fr)
{
if((fr = fopen("podujatia.txt", "r")) == NULL)
{
printf("Neotvoreny subor\n");
return NULL;
}
return fr;
}

void closeFile(FILE *fr)
{
if(fclose(fr) == EOF)
{
printf("Nezatvoreny subor\n");
exit(1);
}
}

int getRecordsNumber(FILE *fr)
{
char pom[32];
int count = 0;

while((fgets(pom, 32, fr)) != NULL)
{
count++;
}

rewind(fr);

return ++count / 7;
}

int getNumberLength(int num)
{
int count = 0;

while(num > 0)
{
num /= 10;
count++;
}

return count;
}

int getVowelCount(char *str)
{
unsigned int i, count = 0;

for(i = 0; i < strlen(str); i++)
{

if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'y' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' || str[i] == 'Y')
count++;
}

return count;
}

void replaceEOL(char *str)
{
unsigned int i;

for(i = 0; i < strlen(str); i++)
{
if(str[i] == '\n')
{
str[i] = '\0';
break;
}
}
}

FILE *funkciaV(FILE *fr)
{
char nazov[32], organizator[32];
int deti, datum;
float cena, cas;

if(fr == NULL)
{
if((fr = openFile(fr)) == NULL)
{
return NULL;
}
}

while((fgets(nazov, 32, fr)) != NULL)
{
fgets(organizator, 32, fr);
fscanf(fr, "%d\n", &deti);
fscanf(fr, "%g\n", &cena);
fscanf(fr, "%d\n", &datum);
fscanf(fr, "%g\n", &cas);

printf("nazov: %s", nazov);
printf("organizator: %s", organizator);
printf("pre deti: %d\n", deti);
printf("cena: %.2f\n", cena);
printf("datum: %08d\n", datum);
printf("cas: %.2f\n\n", cas);
}

rewind(fr);

return fr;
}

void funkciaC(FILE *fr)
{
char pom[32];
int deti, rok, maxrok = 0;
float cas, maxcas = 0.0;

if(fr == NULL)
{
return;
}


while((fgets(pom, 32, fr)) != NULL)
{
fgets(pom, 32, fr);
fscanf(fr, "%d\n", &deti);
fgets(pom, 32, fr);
fscanf(fr, "%d\n", &rok);
fscanf(fr, "%g\n", &cas);

if(deti)
{
rok %= 10000;

if(rok > maxrok)
{
maxrok = rok;
maxcas = cas;
}
else if(rok == maxrok && cas > maxcas)
{
maxcas = cas;
}
}
}

if(maxrok != 0)
printf("%.2f\n", maxcas);

rewind(fr);
}

int funkciaE(FILE *fr, float **field)
{
char pom[32];
int count = 0, i = 0;
float cena, *tempField;

if(fr == NULL)
{
return 0;
}

if(*field != NULL)
{
free(*field);
}

tempField = (float*) malloc(getRecordsNumber(fr) * sizeof(float));

while((fgets(pom, 32, fr)) != NULL)
{
if(i % 7 == 2)
{
fscanf(fr, "%g\n", &cena);
tempField[count] = cena;
count++, i++;
}

i++;
}

rewind(fr);

*field = tempField;

return count;
}

void funkciaR(float *field, int fieldSize)
{
int i, j, len, maxLen = 0;

if(field == NULL)
{
printf("Pole nieje vytvorene\n");
return;
}

for(i = 0; i < fieldSize; i++)
{
if(maxLen < getNumberLength((int)field[i]))
maxLen = getNumberLength((int)field[i]);
}

for(i = 0; i < fieldSize; i++)
{
len = getNumberLength((int)field[i]);

if(len < maxLen)
{
for(j = 0; j < maxLen - len; j++)
{
putchar(' ');
}
}

printf("%.2f\n", field[i]);
}
}

void funkciaH(float *field, int fieldSize)
{
int i, temp, histogram[10];

if(field == NULL)
{
printf("Pole nieje vytvorene\n");
return;
}

for(i = 0; i < 10; i++)
histogram[i] = 0;
}

for(i = 0; i < fieldSize; i++)
{
temp = (int) field[i];
while(temp > 0)
{
histogram[temp % 10]++;
temp /= 10;
}
}

for(i = 9; i >= 0; i--)
{
printf("%d:%d\n", i, histogram[i]);
}
}

void funkciaS(FILE *fr)
{
char pom[32], res[3][32];
int i = 0;

if(fr == NULL)
{
return;
}

strcpy(res[0], "");
strcpy(res[1], "");
strcpy(res[2], "");

while((fgets(pom, 32, fr)) != NULL)
{
if(i % 7 == 0)
{
fgets(pom, 32, fr);

replaceEOL(pom);

if(getVowelCount(pom) > getVowelCount(res[0]))
{
strcpy(res[2], res[1]);
strcpy(res[1], res[0]);
strcpy(res[0], pom);
}
else if(getVowelCount(pom) > getVowelCount(res[1]))
{
strcpy(res[2], res[1]);
strcpy(res[1], pom);
}
else if(getVowelCount(pom) > getVowelCount(res[2]))
{
strcpy(res[2], pom);
}

i++;
}

i++;
}

rewind(fr);

for(i = 2; i >= 0; i--)
{
if(strlen(res[i]) != 0)
printf("%s:%d\n", res[i], getVowelCount(res[i]));
}
}
int main()
{
FILE *fr = NULL;
float *field = NULL;
int fieldSize = 0;
char cmd;

while((cmd = getchar()) != 'k')
{
switch(cmd)
{
case 'v':
getchar();
fr = funkciaV(fr);
break;
case 'c':
getchar();
funkciaC(fr);
break;
case 'e':
getchar();
fieldSize = funkciaE(fr, &field);
break;
case 'r':
getchar();
funkciaR(field, fieldSize);
break;
case 'h':
getchar();
funkciaH(field, fieldSize);
break;
case 's':
getchar();
funkciaS(fr);
break;
}

}

if(fr != NULL)
closeFile(fr);

return 1;
}
