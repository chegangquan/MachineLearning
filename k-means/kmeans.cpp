// k-means.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_DEPRECATE；
#pragma warning(disable:4996)
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include<string>
#include<sstream>
#include <fstream>
using namespace std;

//int data_row = 106;  //数据的总行数
//int data_col = 11;  //数据的总列数
//const char* filename = "E:\\score.txt";
//string targets_filename = "E:\\targets.csv";
//string center_filename = "E:\\center.csv";

int data_row = 20;  //数据的总行数
int data_col = 2;  //数据的总列数
const char* filename = "E:\\data.txt";
//string targets_filename = "E:\\targets_data.csv";
//string center_filename = "E:\\center_data.csv";

//字符串分割
void split(const string& str, vector<string>& str_vec, const char delimeter) {
	istringstream iss(str);
	string temp;
	while (getline(iss, temp, delimeter)) {
		str_vec.push_back(temp);
	}
}

//创建double[][]数组
double** create_double_2d(int row, int col) {
	double** maxtri = new double* [row];
	for (int i = 0; i < row; i++) {
		maxtri[i] = new double[col];
		for (int j = 0; j < col; j++) {
			maxtri[i][j] = 0;
		}
	}
	return maxtri;
}

//输出double[][]数组
void print_double_2d(double** data, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << data[i][j] << ' ';
		}
		cout << endl;
	}
}

void print_int_1d(int* data, int k) {
	for (int i = 0; i < k; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
}

//string to double
double string2double(string s) {
	double n = atof(s.c_str());
	return n;
}

//读取文件数据
double** readfile_double2d(string filename, int row, int col) {
	ifstream fin(filename);
	string s;
	vector<string>str_vec;
	double** data;
	double temp;
	while (getline(fin, s))  //按行读取文件数据，并根据逗号进行分割，将每个数字存到str_vec里
	{
		split(s, str_vec, ',');
	}
	data = create_double_2d(row, col);  //二维data数组存储全部数据
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp = string2double(str_vec[i * col + j]);  //类型转换
			data[i][j] = temp;
		}
	}
	return data;
}

int* readfile_int_1d(string filename, int col) {
	ifstream fin(filename);
	string s;
	vector<string>str_vec;
	int* data = new int [col];
	int temp;
	while (getline(fin, s))  //按行读取文件数据，并根据逗号进行分割，将每个数字存到str_vec里
	{
		split(s, str_vec, ',');
	}
	for (int j = 0; j < col; j++) {
		temp = int(string2double(str_vec[j]));  //类型转换
		data[j] = temp;
	}
	return data;
}

//随机质点函数
double** srand_centre(int k, double** data)
{
	srand(time(NULL));
	int* a;  //记录随机质心的索引值
	a = new int[k];
	for (int i = 0; i < k; i++)
	{
		a[i] = rand() % data_row;
	}
	int col = data_col;
	double** centre = new double* [k];  //记录随机质心的数据
	for (int i = 0; i < k; i++)
	{
		centre[i] = data[a[i]];
	}
	return centre;
}

//计算距离
double distance(double* a, double* b, int attr_len) {
	double dis = 0;
	double temp;
	for (int i = 0; i < attr_len; i++) {
		temp = (a[i] - b[i]) * (a[i] - b[i]);
		dis = dis + temp;
	}
	dis = sqrt(dis);
	return dis;
}

//计算类别
int* calculate_target(double** data, double** center, int k) {
	int* targets = new int[data_row];  //每行数据归属的类别标签
	double dis;  //距离中心点的距离

	//根据中心点的位置计算每行数据的类别
	for (int i = 0; i < data_row; i++) {
		double min = 999;
		int minindex = 0;
		for (int j = 0; j < k; j++) {
			dis = distance(data[i], center[j], data_col);  //计算距离
			if (dis < min)  //记录距离最短的类别
			{
				min = dis;
				minindex = j;
			}
		}
		targets[i] = minindex;
	}
	return targets;
}

void save_targets_center(int* targets, double** center, int k) {
	string targets_filename = "E:\\k=" + to_string(k) + " targets_data.csv";
	string center_filename = "E:\\k=" +to_string(k) + " center_data.csv";
	ofstream a(targets_filename);
	ofstream b(center_filename);
	for (int i = 0; i < data_row; i++) {
		a << targets[i];
		if (i != data_row - 1)
			a << ",";
	}
	a.close();
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < data_col; j++) {
			b << center[i][j];
			if (j != data_col - 1)
				b << ",";
		}
		b << "\n";
	}
	b.close();
}

void save_wss(double* wss, int k_max) {
	string wss_filename = "E:\\k_max=" + to_string(k_max) + " wss_data.csv";
	ofstream a(wss_filename);
	for (int i = 0; i < k_max; i++) {
		a << wss[i];
		if (i != k_max - 1)
			a << ",";
	}
	a.close();
}

void kmeans(double** data, int k = 2) {
	int run_time = 0;
	bool flag = true;

	int* targets = new int[data_row];  //每行数据的类别标签
	int* newtargets = new int[data_row];  //每行数据的类别标签
	double** newcenter = create_double_2d(k, data_col);  //更新后的中心点
	double** total = create_double_2d(k, data_col);

	double** center;
	center = srand_centre(k, data);  //随机中心点
	print_double_2d(center, k, data_col);
	cout << endl;

	int* count = new int[k];
	for (int j = 0; j < k; j++)
	{
		count[j] = 0;
	}

	while (flag)
	{
		run_time++;
		flag = false;
		targets = calculate_target(data, center, k);  //新计算的target

		// 计算新的中心点，并判断中心点有无变化
		for (int i = 0; i < data_row; i++)
		{
			for (int j = 0; j < k; j++)
			{
				if (targets[i] == j) {
					for (int t = 0; t < data_col; t++) {
						total[j][t] += data[i][t];
					}
					count[j] += 1;
				}
			}
		}
		for (int j = 0; j < k; j++)
		{
			for (int t = 0; t < data_col; t++) {
				newcenter[j][t] = (int(total[j][t] / count[j] * 100)) / 100.0;  //新的质心，数据保留两位小数
				if (newcenter[j][t] != center[j][t]) {  //如果新的质心于旧质心不一样，flag = true
					flag = true;
				}
			}
		}

		// count[k]数组清零
		for (int i = 0; i < k; i++) {
			count[i] = 0;
		}

		// total[k][data_col]数组清零
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < data_col; j++) {
				total[i][j] = 0;
			}
		}

		// 旧中心点等于新中心点
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < data_col; j++) {
				center[i][j] = newcenter[i][j];
			}
		}

		print_double_2d(center, k, data_col);
		cout << endl;
	}

	print_int_1d(targets, data_row);
	cout << "迭代次数" << run_time;

	save_targets_center(targets, center, k);  //保存结果
}

//WSS计算函数
void wss(double** data, int k_max) {
	int* targets;
	double** center;
	double* wss = new double[k_max];
	for (int i = 0; i < k_max; i++) {
		wss[i] = 0.0;
	}

	for (int i = 1; i <= k_max; i++) {
		string targets_filename = "E:\\k=" + to_string(i) + " targets_data.csv";
		string center_filename = "E:\\k=" + to_string(i) + " center_data.csv";
		kmeans(data, i);  // 进行聚类
		center = readfile_double2d(center_filename, i, data_col); // 读取中心点数据
		targets = readfile_int_1d(targets_filename, data_row);  // 读取类别数据
		for (int p = 0; p < data_row; p++) {
			for (int lable = 0; lable < i; lable++) {
				if (targets[p] == lable) {  // 判断类别
					wss[i - 1] += distance(data[p], center[lable], data_col);  // 计算距离类中心的距离
				}
			}
		}
	}
	save_wss(wss, k_max);
}

int main()
{
	int k = 2;
	//构建data_row*data_col的数组来存储数据
	double** data;
	data = readfile_double2d(filename, data_row, data_col);  //读数据


	/*kmeans(data, k);*/

	int k_max = 5;
	wss(data, k_max);
}