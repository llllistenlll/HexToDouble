#ifndef TOOLS_H
#define TOOLS_H

#endif // TOOLS_H

unsigned int getbitu_(const unsigned char *buff, int pos, int len)
{


    unsigned int bits=0;
    int i;
    for (i=pos;i<pos+len;i++)
    {
        bits=(bits<<1)+((buff[i/8]>>(7-i%8))&1u);
    }
    return bits;
}




double Hex2Double(const unsigned char* buf)
{
double value = 0;
unsigned int i = 0;
unsigned int num,temp;
int num2;
bool flags1 = false;
bool flags2 = false;

num = getbitu_(buf,i,1);             i += 1;
num2 = getbitu_(buf,i,11) - 1023;    i += 11;

if(num2 >= 0)
{
    flags2 = true;
    while(1)
    {
        flags1 = true;
        if(flags2)
        {
            flags2 = false;
            value += 1 * pow(2,num2); num2--;
        }

        temp = getbitu_(buf,i,1);    i += 1;
        value += temp * pow(2,num2); num2--;
        if(num2 < 0 || i == 64);
            break;
    }
}
while(1)
{
    if(flags1)
    {
        temp = getbitu_(buf,i,1);    i += 1;
        value += temp * pow(2,num2); num2--;
    }
    else
    {
        flags1 = true;
        value += 1 * pow(2,num2); num2--;
    }

    if(i == 64)
        break;
}

if(num == 1)
    value *= -1;

return value;
}



void DoubleToHex(double m,unsigned char* buf)
{
int i;
int m1;//double型数据的整数部分
double m2,m3;//double型数据的小数部分
int num1;//阶数的值
int num2;//尾数的位数
long long int temp1 = 0;
long long int temp2 = 0;

//符号位判断
if(m >= 0)
{
    buf[0] = 0;
}
else
{
    buf[0] = 128;
}
m = fabs(m);

//将double型数分解成整数部分和小数部分
m1 = floor(m);
m2 = m - m1;

//阶数计算
if(m1 > 0)
{
    for(num1 = 0,temp1 = 1; 2*temp1 <= m1; num1++)
    {
        temp1 *= 2;
    }
    num1 += 1023;
}
else
{
    for(num1 = 0, m3 = m2; m3 <= 1; num1++)
    {
        m3 *= 2;
    }
    num1 = 1023 - num1;
}

buf[0] += ((num1 >> 4) & 0x0ff);
buf[1] = (num1 & 0x0f) << 4;

//尾数计算
if(m1 > 0)
{
    for(num1 = 0; m1/2 > 0; num1++)
    {
        temp1 = (temp1 << 1) + m1%2;
        m1 = m1/2;
    }
    for(i = 0; i < num1; i++)
    {
        temp2 = (temp2 << 1) + (temp1 & (0x01));
        temp1 = temp1 >> 1;
    }
    for(i = 0; i < 52 - num1; i++)
    {
        temp2 = (temp2 << 1) + floor(m2*2);
        m2 = m2*2 - floor(m2*2);
    }
}
else
{
    do
    {
        m2 *= 2;
    }while(m2 < 1);
    m2 -= floor(m2);
    for(i = 0; i < 52; i++)
    {
        temp2 = (temp2 << 1) + floor(m2*2);
        m2 = m2*2 - floor(m2*2);
    }
}

//将转换后的数据存放到数组中
for(i = 7; i > 1; i--)
{
    buf[i] = temp2 & 0x0ff;
    temp2 = temp2 >> 8;
}
buf[1] += temp2 & 0x0f;
}

