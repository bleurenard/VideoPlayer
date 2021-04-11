/*=================================================================
 * Extract Background & Foreground Model by ViBe Algorithm using OpenCV Library.
 *
 * Copyright (C) 2017 Chandler Geng. All rights reserved.
 *
 *     This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *     You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
===================================================================
*/

#include <iostream>
#include <cstdio>
#include"opencv2/opencv.hpp"  
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <core/core_c.h>
#include <imgproc/types_c.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace cv;
using namespace std;

// ÿ�����ص����������Ĭ��ֵ
// the Default Number of pixel's samples
#define DEFAULT_NUM_SAMPLES  20

// #minָ��Ĭ��ֵ
// the Default Match Number of make pixel as Background
#define DEFAULT_MIN_MATCHES  2

// Sqthere�뾶Ĭ��ֵ
// the Default Radius of pixel value
#define DEFAULT_RADIUS 20

// �Ӳ�������Ĭ��ֵ
// the Default the probability of random sample
#define DEFAULT_RANDOM_SAMPLE 16

class ViBe
{
public:
    ViBe(int num_sam = DEFAULT_NUM_SAMPLES,
        int min_match = DEFAULT_MIN_MATCHES,
        int r = DEFAULT_RADIUS,
        int rand_sam = DEFAULT_RANDOM_SAMPLE);
    ~ViBe(void);

    // ����ģ�ͳ�ʼ��
    // Init Background Model.
    void init(Mat img);

    // �����һ֡ͼ��
    // Process First Frame of Video Query
    void ProcessFirstFrame(Mat img);

    // ���� ViBe �㷨����ȡǰ�����򲢸��±���ģ��������
    // Run the ViBe Algorithm: Extract Foreground Areas & Update Background Model Sample Library.
    void Run(Mat img);

    // ��ȡǰ��ģ�Ͷ�ֵͼ��
    // get Foreground Model Binary Image.
    Mat getFGModel();

    // ɾ��������
    // Delete Sample Library.
    void deleteSamples();

    // x���ھӵ�
    // x's neighborhood points
    int c_xoff[9];

    // y���ھӵ�
    // y's neighborhood points
    int c_yoff[9];

private:
    // ������
    // Sample Library, size = img.rows * img.cols *  DEFAULT_NUM_SAMPLES
    unsigned char*** samples;

    // ǰ��ģ�Ͷ�ֵͼ��
    // Foreground Model Binary Image
    Mat FGModel;

    // ÿ�����ص����������
    // Number of pixel's samples
    int num_samples;

    // #minָ��
    // Match Number of make pixel as Background
    int num_min_matches;

    // Sqthere�뾶
    // Radius of pixel value
    int radius;

    // �Ӳ�������
    // the probability of random sample
    int random_sample;
};