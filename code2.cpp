//
//  main.cpp
//  线性分类器:线性分类器
//
//  Created by Qi Zheng on 2018/4/28.
//  Copyright © 2019年 Matrix. All rights reserved.
//  簡單的生活
//  何嘗不是一場華麗的冒險

#include <cmath>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <random>
using namespace std;

double normalCFD(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

int main(){
    vector<double> omega1={-3.9847,-3.5549,-1.2401,-0.9780,-0.7932,-2.8531,-2.7605,-3.7287, -3.5414,-2.2692,-3.4549,-3.0752,-3.9934, -0.9780,-1.5799,-1.4885, -0.7431,-0.4221,-1.1186,-2.3462,-1.0826,-3.4196,-1.3193,-0.8367, -0.6579,-2.9683};
    vector<double> omega2={2.8792,0.7932,1.1882,3.0682,4.2532,0.3271,0.9846,2.7648,2.6588};
    int count1=(int)omega1.size();
    int count2=(int)omega2.size();
    vector<double>::iterator iterator1,iterator2;
    //计算两类样本数据的均值与方差
    double sum=0,squrt=0;
    double average1,average2;
    double sigma1,sigma2;
    for (iterator1=omega1.begin(); iterator1!=omega1.end(); iterator1++) {
        sum+=*iterator1;
        squrt+=(*iterator1)*(*iterator1);
    }
    average1=sum/count1;
    sigma1=squrt/count1-average1*average1;
    sum=squrt=0;
    for (iterator2=omega2.begin(); iterator2!=omega2.end(); iterator2++) {
        sum+=*iterator2;
        squrt+=(*iterator2)*(*iterator2);
    }
    average2=sum/count2;
    sigma2=squrt/count2-average2*average2;
    cout<<"正常类的平均值与方差为："<<average1<<sigma1<<endl;
    cout<<"非正常类的平均值与方差为："<<average2<<sigma2<<endl;
    double viewdata;
    cout<<"请输入观测值"<<endl;cin>>viewdata;
    //带入标准正态分布计算条件概率
    double value1=(viewdata-average1)/sigma1;
    double value2=(viewdata-average2)/sigma2;
    double x_omega1=normalCFD(value1),x_omega2=normalCFD(value2);
    //根据贝叶斯概率分布定理计算后验概率
    double omega1_x=(x_omega1*0.9)/(x_omega1*0.9+x_omega2*0.1);
    double omega2_x=(x_omega2*0.1)/(x_omega1*0.9+x_omega2*0.1);
    double alpha1_x=omega2_x*1;
    double alpha2_x=omega1_x*6;
    if (alpha1_x>alpha2_x) {
        cout<<"应该选择决策2，即将样本归入非正常类"<<endl;
    }
    else{
        cout<<"应该选择决策1，即将样本归入正常类"<<endl;
    }
    return 0;
}