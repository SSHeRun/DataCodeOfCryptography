#include "stdafx.h"
#include "BigInt.h"

//****************************************
BigInt::BigInt()
{
    memset(data,0,sizeof(data));
    after=0;
    sign=1;
    before=0;
}
//***********************************************************
BigInt::BigInt( string str)
{
    memset(data,0,sizeof(data));
    if(str[0]!='-')
        sign=1;
    else sign=-1;
    if(str[0]=='-' || str[0]=='+')
        str.erase(0,1);
    unsigned int loc=str.find('.',0);
    int len=str.length();
    if(loc==string::npos)
    {
        after=0;
        before=len;
        for(int i=len-1,j=pos;i>=0;--i,++j)
        {
            data[j]=str[i]-'0';
        }
    }
    else
    {
        for(int i=loc-1,j=pos;i>=0;--i,++j)
        {
            data[j]=str[i]-'0';
        }
        before=loc;
        for(i=loc+1,j=pos-1;i<len;++i,--j)
        {
            data[j]=str[i]-'0';
        }
        after=len-loc-1;
    }
    while(after>0 && data[pos-after]==0)
        --after;
	
    while(before>0 && data[pos+before-1]==0)
        --before;
}
//***********************************************************
//*********************************************************************
BigInt BigInt::NormalAdd(const BigInt & a)
{
    BigInt res;
    res.sign=sign;
    res.after=a.after>after ? a.after:after;
    int bef=a.before>before ? a.before: before;
    for(int i=pos-res.after; i<pos+bef; ++i)
    {
        res.data[i]+=data[i]+a.data[i];
        if(res.data[i]>=BASE)
        {
            res.data[i+1]+=res.data[i]/BASE;
            res.data[i]%=BASE;
        }
    }
    while(res.data[pos+bef])
    {
        res.data[pos+bef+1]+=res.data[pos+bef]/BASE;
        res.data[pos+bef]%=BASE;
        ++bef;
    }
    res.before=bef;
    while(res.after>0 && res.data[pos-res.after]==0)
    {
        --res.after;
    }
    return res;
}
//********************************************************
int BigInt::AbsCompare(const BigInt &a)
{
    if(before>a.before) return 1;
    else if(before<a.before) return -1;
    else 
    {
        int t=after>a.after ? after: a.after;
        t=pos-t;
        for(int i=pos+before-1; i>=t; --i)
        {
            if(data[i]>a.data[i])
                return 1;
            else if(data[i]<a.data[i])
                return -1;
        }
    }
    return 0;
}
//*********************************************************
int BigInt::Compare(const BigInt &a)
{
    if(sign>a.sign) return 1;
    else if(sign<a.sign) return -1;
    else return sign*AbsCompare(a);
}
//**********************************************************
BigInt BigInt::NormalSubtract( const BigInt  &a)
{
    BigInt res;
    res.after=after>a.after ? after: a.after;
    for(int i=pos-res.after; i<pos+before; ++i)
    {
        res.data[i]=data[i]-a.data[i];
    }
    for(i=pos-res.after; i<pos+before; ++i)
    {
        if(res.data[i]<0)
        {
            res.data[i]+=BASE;
            res.data[i+1]-=1;
        }
    }
    int bef=before;
    while(bef)
    {
        if(res.data[pos+bef-1])
            break;
        --bef;
    }
    res.before=bef;
    while(res.after>0 && res.data[pos-res.after]==0)
    {
        --res.after;
    }
    return res;
}
//*********************************************************
BigInt BigInt::Add( BigInt &a)
{
    if(sign==a.sign)
        return NormalAdd(a);
    BigInt res;
    if(sign>a.sign)
    {
        if(AbsCompare(a)>=0)  
        {
            res=NormalSubtract(a);
            res.sign=1;
        }
        else
        {
            res=a.NormalSubtract(*this);
            res.sign=-1;
        }
    }
    else if(sign<a.sign)
    {
        if(AbsCompare(a)>0)
        {
            res=NormalSubtract(a);
            res.sign=-1;
        }
        else 
        {
            res=a.NormalSubtract(*this);
            res.sign=1;
        }
    }
    return res;
}
//********************************************************
BigInt BigInt::Subtract(BigInt &a)
{
    if(sign!=a.sign)
    {
        return NormalAdd(a);
    }
    BigInt res;
    if(sign==1)
    {
        if(AbsCompare(a)>=0)
        {
            res=NormalSubtract(a);
            res.sign=1;
        }
        else 
        {
            res=a.NormalSubtract(*this);
            res.sign=-1;
        }
    }
    else if(sign=-1)
    {
        if(AbsCompare(a)>0)
        {
            res=NormalSubtract(a);
            res.sign=-1;
        }
        else
        {
            res=a.NormalSubtract(*this);
            res.sign=1;
        }
    }
    return res;
}
//********************************************************
BigInt BigInt::Mul(const BigInt &a)
{
    BigInt res;
    if(sign!=a.sign)  res.sign=-1;
    else res.sign=1;
    int len=before+after;
    int alen=a.before+a.after;
    for(int i=0,j=pos-after; i<len; ++i,++j)   //计算
    {
        for(int k=0,t=a.pos-a.after; k<alen; ++k,++t)
        {
            res.data[i+k]+=data[j]*a.data[t];
        }
    }
    for(i=0;i<len+alen;++i)  //进位
    {
        if(res.data[i]>=BASE)
        {
            res.data[i+1]+=res.data[i]/BASE;
            res.data[i]%=BASE;
        }
    }
    int shift=pos-after-a.after;                //计算应该移动的位数
    for(i=len+alen; i>=0; --i)
    {
        res.data[i+shift]=res.data[i];
        res.data[i]=0;
    }
    i=0;
    while(i<pos)
    {
        if(res.data[i]>0) break;
        ++i;
    }
    res.after=pos-i;
    int bef=alen+len+shift;
    if(res.data[bef]>0)
    {
        while(res.data[bef])
        {
            res.data[bef+1]=res.data[bef]/BASE;
            res.data[bef]%=BASE;
            ++bef;
        }
        res.before=bef-pos;
    }
    else 
    {
        while(bef>=pos)
        {
            if(res.data[bef]>0) break;
            --bef;
        }
        res.before=bef-pos+1;
    }
    return res;
}
//********************************************************
BigInt operator+(const BigInt &a,const BigInt &b)
{
	return const_cast<BigInt &>( a ).Add( const_cast<BigInt &>( b ) );
}

BigInt operator*(const BigInt &a,const BigInt &b)
{
	return const_cast<BigInt &>( a ).Mul( const_cast<BigInt &>( b ) );
}

BigInt operator-(const BigInt &a,const BigInt &b)
{
	return const_cast<BigInt &>( a ).Subtract( const_cast<BigInt &>( b ) );
}

std::ostream& operator<<(std::ostream &os,BigInt &a)
{
    if(a.sign==-1)
        os<<'-';
    for(int i=a.before+a.pos-1; i>=a.pos; --i)
        os<<a.data[i];
    if(a.after>0)
    {
        os<<'.';
        for(int i=a.pos-1; i>=a.pos-a.after; --i)
            os<<a.data[i];
    }
    if(a.after==0 && a.before==0)
        os<<'0';
    return os;
}
//********************************************************
int BigInt::pos=200;
