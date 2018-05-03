//
//  main.cpp
//  线性分类器:线性分类器
//
//  Created by Qi Zheng on 2018/4/28.
//  Copyright © 2019年 Matrix. All rights reserved.
//  簡單的生活
//  何嘗不是一場華麗的冒險

#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN=1000;
const double pi=3.1415926;
ifstream cin1("FEMALE.TXT");
ifstream cin2("MALE.TXT");
ifstream cin3("test2.txt");
ofstream cout1("result.txt");
struct HUMAN
{
    double height;
    double weight;
};
HUMAN female[MAXN];
HUMAN male[MAXN];
int female_num;
int male_num;

double P_female;
double P_male;
struct NORMAL
{
  double mu1;
  double mu2;
  double delta1;
  double delta2;
  double rho;
};
NORMAL female_normal;
NORMAL male_normal;
/*
读入文件数据
*/
void In()
{
    male_num=0;
    female_num=0;
    while(cin1>>female[female_num+1].height>>female[female_num+1].weight)
    {
        female_num++;
    }
    while(cin2>>male[male_num+1].height>>male[male_num+1].weight)
    {
        male_num++;
    }
}
void Init()
{
      P_female=0.5;
      P_male=0.5;
}
/*
读入样本数量个样本，并求出该样本的二维正态分布
*/
void Normalization(struct HUMAN *human,int human_num,struct NORMAL &human_normal)
{
    double mu1,mu2,delta1,delta2,rho;
    mu1=0;mu2=0;delta1=0;delta2=0,rho=0;
    for(int i=1;i<=human_num;i++)
    {
          mu1+=human[i].height;
          mu2+=human[i].weight;
    }
    mu1/=human_num;
    mu2/=human_num;

    for(int i=1;i<=human_num;i++)
    {
          delta1+=(human[i].height-mu1)*(human[i].height-mu1);
          delta2+=(human[i].weight-mu2)*(human[i].weight-mu2);
    }
    delta1/=human_num;
    delta2/=human_num;
    delta1=sqrt(delta1);
    delta2=sqrt(delta2);
    for(int i=1;i<=human_num;i++)
    {
          rho+=human[i].height*human[i].weight;
    }
    rho/=human_num;
    rho-=mu1*mu2;
    rho/=(delta1*delta2);
    human_normal.mu1=mu1;
    human_normal.mu2=mu2;
    human_normal.delta1=delta1;
    human_normal.delta2=delta2;
    human_normal.rho=rho;
    cout<<mu1<<" "<<delta1<<" "<<mu2<<" "<<delta2<<" "<<rho<<endl;
}
/*
在分布为normal的条件下特征为(x1,x2)的条件概率
*/

double P(struct NORMAL &normal,double x1,double x2)
{
    double ans;
    double mu1=normal.mu1;
    double mu2=normal.mu2;
    double delta1=normal.delta1;
    double delta2=normal.delta2;
    double rho=normal.rho;
     rho=0;
    ans=(1/(2*pi*delta1*delta2*        sqrt(1-rho*rho)            ))*exp(-1/(2*sqrt(1-rho*rho)   )*(             ((x1-mu1)*(x1-mu1))/(delta1*delta1)   +   ((x2-mu2)*(x2-mu2))/(delta2*delta2)   -    (2*rho*(x1-mu1)*(x2-mu2))/(delta1*delta2)                                   )   );
    return ans;
}
/*
归为normal的后验概率
t为0表示female，1表示male
*/
double Posterior_probability1(double x1,double x2,bool t)
{
    double Pw;
    struct NORMAL normal;
    if(t==0)return (P(female_normal,x1,x2)*P_female)/(P(female_normal,x1,x2)*P_female+P(male_normal,x1,x2)*P_male);
    else return (P(male_normal,x1,x2)*P_male)/(P(female_normal,x1,x2)*P_female+P(male_normal,x1,x2)*P_male);
}
/*
判断是哪个类别，返回0表示female,1表示male
*/
bool Classify(double x1,double x2)
{
    //cout<<Posterior_probability1(x1,x2,0)<<" "<<Posterior_probability1(x1,x2,1)<<endl;
    if(Posterior_probability1(x1,x2,0)>=Posterior_probability1(x1,x2,1))return 0;
    else return 1;
}
/*
得到错误率并将错误率输出到result.txt中
*/
void Find_error_rate()
{
    double height,weight;
    char c;
    int right_num=0;
    int wrong_num=0;
    while(cin3>>height>>weight>>c)
    {
        if(   (c=='f' || c=='F')   && Classify(height,weight)==0)//分类为女性并且正确
             right_num++;
        else if(   (c=='m' || c=='M')   && Classify(height,weight)==1)//分类为男性并且正确
             right_num++;
        else
            wrong_num++;

        cout1<<height<<" "<<weight<<" "<<Classify(height,weight)<<endl;
    }
    cout<<"error rate is "<<(double)wrong_num/(double)(wrong_num+right_num)<<endl;
}
int main()
{
    In();
    Init();
    Normalization(female,female_num,female_normal);
    Normalization(male,male_num,male_normal);
    //female_normal.rho=0;
    //male_normal.rho=0;
    Find_error_rate();
    return 0;
}
