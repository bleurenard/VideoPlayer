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

#include "Vibe.h"

/*===================================================================
 * ���캯����ViBe
 * ˵������ʼ��ViBe�㷨���ֲ�����
 * ������
 *   int num_sam:  ÿ�����ص����������
 *   int min_match:  #minָ��
 *   int r:  Sqthere�뾶
 *   int rand_sam:  �Ӳ�������
 *------------------------------------------------------------------
 * Constructed Function: ViBe
 *
 * Summary:
 *   Init several arguments of ViBe Algorithm.
 *
 * Arguments:
 *   int num_sam - Number of pixel's samples
 *   int min_match - Match Number of make pixel as Background
 *   int r - Radius of pixel value
 *   int rand_sam - the probability of random sample
=====================================================================
*/
ViBe::ViBe(int num_sam, int min_match, int r, int rand_sam)
{
    num_samples = num_sam;
    num_min_matches = min_match;
    radius = r;
    random_sample = rand_sam;
    int c_off[9] = { -1, 0, 1, -1, 1, -1, 0, 1, 0 };
    for (int i = 0; i < 9; i++) {
        c_xoff[i] = c_yoff[i] = c_off[i];
    }
}

/*===================================================================
 * ����������~ViBe
 * ˵�����ͷ��������ڴ棻
 *------------------------------------------------------------------
 * Destructor Function: ~ViBe
 *
 * Summary:
 *   Release the memory of Sample Library.
=====================================================================
*/
ViBe::~ViBe()
{
    deleteSamples();
}

/*===================================================================
 * ��������init
 * ˵��������ģ�ͳ�ʼ����
 *    Ϊ���������ռ䣻
 * ������
 *   Mat img:  Դͼ��
 * ����ֵ��void
 *------------------------------------------------------------------
 * Function: init
 *
 * Summary:
 *   Init Background Model.
 *   Assign space for sample library.
 *   Read the first frame of video query as background model, then select pixel's
 * neighbourhood pixels randomly and fill the sample library.
 *
 * Arguments:
 *   Mat img - source image
 *
 * Returns:
 *   void
=====================================================================
*/
void ViBe::init(Mat img)
{
    // ��̬������ά���飬samples[][][num_samples]�洢ǰ�����������Ĵ���
    // Dynamic Assign 3-D Array.
    // sample[img.rows][img.cols][num_samples] is a 3-D Array which includes all pixels' samples.
    samples = new unsigned char** [img.rows];
    for (int i = 0; i < img.rows; i++)
    {
        samples[i] = new uchar * [img.cols];
        for (int j = 0; j < img.cols; j++)
        {
            // �����У���num_samples֮�������һ��ֵ������ͳ�Ƹ����ص�������Ϊǰ���Ĵ�����
            // the '+ 1' in 'num_samples + 1', it's used to count times of this pixel regarded as foreground pixel.
            samples[i][j] = new uchar[num_samples + 1];
            for (int k = 0; k < num_samples + 1; k++)
            {
                // ����������ʱ����������ȫ����ʼ��Ϊ0
                // All Samples init as 0 When Creating Sample Library.
                samples[i][j][k] = 0;
            }
        }
    }

    FGModel = Mat::zeros(img.size(), CV_8UC1);
}

/*===================================================================
 * ��������ProcessFirstFrame
 * ˵���������һ֡ͼ��
 *    ��ȡ��Ƶ���е�һ֡�������ѡȡ���ص�������������������⣬��ʼ������ģ�ͣ�
 * ������
 *   Mat img:  Դͼ��
 * ����ֵ��void
 *------------------------------------------------------------------
 * Function: ProcessFirstFrame
 *
 * Summary:
 *   Process First Frame of Video Query, then select pixel's neighbourhood pixels
 * randomly and fill the sample library, and init Background Model.
 *
 * Arguments:
 *   Mat img - source image
 *
 * Returns:
 *   void
=====================================================================
*/
void ViBe::ProcessFirstFrame(Mat img)
{
    RNG rng;
    int row, col;

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            for (int k = 0; k < num_samples; k++)
            {
                // ���ѡ��num_samples���������ص㣬��������ģ��
                // Random pick up num_samples pixel in neighbourhood to construct the model
                int random;
                random = rng.uniform(0, 9); row = i + c_yoff[random];
                random = rng.uniform(0, 9); col = j + c_xoff[random];

                // ��ֹѡȡ�����ص�Խ��
                // Protect Pixel from Crossing the border
                if (row < 0)  row = 0;
                if (row >= img.rows)  row = img.rows - 1;
                if (col < 0)  col = 0;
                if (col >= img.cols)   col = img.cols - 1;

                // Ϊ�����⸳���ֵ
                // Set random pixel's Value for Sample Library
                samples[i][j][k] = img.at<uchar>(row, col);
            }
        }
    }
}

/*===================================================================
 * ��������Run
 * ˵�������� ViBe �㷨����ȡǰ�����򲢸��±���ģ�������⣻
 * ������
 *   Mat img:  Դͼ��
 * ����ֵ��void
 *------------------------------------------------------------------
 * Function: Run
 *
 * Summary:
 *   Run the ViBe Algorithm: Extract Foreground Areas & Update Background Model Sample Library.
 *
 * Arguments:
 *   Mat img - source image
 *
 * Returns:
 *   void
=====================================================================
*/
void ViBe::Run(Mat img)
{
    RNG rng;
    int k = 0, dist = 0, matches = 0;
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            //========================================
            //        ǰ����ȡ   |   Extract Foreground Areas
            //========================================
            /*===================================================================
             * ˵�������㵱ǰ����ֵ���������ƥ�������
             * ������
             *   int matches: ��ǰ����ֵ����������ֵ֮��С����ֵ��ΧRADIUS�ĸ�����
             *   int count: ����������Ļ��������
             *------------------------------------------------------------------
             * Summary:
             *   Count how many samples in library can match to current pixel value.
             *
             * Argumen:
             *   int matches - the Number of samples whose value subtract current pixel's value
             *          is less than RADIUS.
             *   int count - the temp variance for going through sample library.
            =====================================================================
            */
            for (k = 0, matches = 0; matches < num_min_matches && k < num_samples; k++)
            {
                dist = abs(samples[i][j][k] - img.at<uchar>(i, j));
                if (dist < radius)
                    matches++;
            }
            /*===================================================================
             * ˵����
             *      ��ǰ����ֵ����������ֵƥ������ϸߣ�����Ϊ�Ǳ������ص㣻
             *      ��ʱ����ǰ��ͳ�ƴ���������ǰ��ģ�͡����¸�����ģ������ֵ�����¸����ص��������ص��ģ������ֵ
             *------------------------------------------------------------------
             * Summary:
             *   the Match Times of current pixel value and samples in library is large enough to
             * regard current pixel as a Background pixel.
             *   Then it needs to be done:
             *   - Run the times of Foreground Statistic
             *   - Run Foreground Model
             *   - Run model sample library of this pixel probably
             *   - Run model sample library of this pixel's neighborhood pixel probably
            =====================================================================
            */
            if (matches >= num_min_matches)
            {
                // �Ѿ���Ϊ�Ǳ������أ��ʸ����ص�ǰ��ͳ�ƴ�����0
                // This pixel has regard as a background pixel, so the count of this pixel's foreground statistic set as 0
                samples[i][j][num_samples] = 0;

                // �����ص㱻��ǰ��ģ������ֵ��0
                // Set Foreground Model's pixel as 0
                FGModel.at<uchar>(i, j) = 0;
            }
            /*===================================================================
             * ˵����
             *      ��ǰ����ֵ����������ֵƥ������ϵͣ�����Ϊ��ǰ�����ص㣻
             *      ��ʱ��Ҫ����ǰ��ͳ�ƴ������жϸ���ǰ��ģ�ͣ�
             *------------------------------------------------------------------
             * Summary:
             *   the Match Times of current pixel value and samples in library is small enough to
             * regard current pixel as a Foreground pixel.
             *   Then it needs to be done:
             *   - Run the times of Foreground Statistic
             *   - Judge and Run Foreground Model
            =====================================================================
            */
            else
            {
                // �Ѿ���Ϊ��ǰ�����أ��ʸ����ص�ǰ��ͳ�ƴ���+1
                // This pixel has regard as a foreground pixel, so the count of this pixel's foreground statistic plus 1
                samples[i][j][num_samples]++;

                // �����ص㱻��ǰ��ģ������ֵ��255
                // Set Foreground Model's pixel as 255
                FGModel.at<uchar>(i, j) = 255;

                // ���ĳ�����ص�����50�α����Ϊǰ��������Ϊһ�龲ֹ��������Ϊ�˶����������Ϊ������
                // if this pixel is regarded as foreground for more than 50 times, then we regard this static area as dynamic area by mistake, and Run this pixel as background one.
                if (samples[i][j][num_samples] > 50)
                {
                    int random = rng.uniform(0, num_samples);
                    samples[i][j][random] = img.at<uchar>(i, j);
                }
            }

            //================================================================
            //        ����ģ��������    |    Update Background Model Sample Library
            //================================================================
            if (matches >= num_min_matches)
            {
                // �Ѿ���Ϊ�������Ǳ������أ���ô���� 1 / �� �ĸ���ȥ�����Լ���ģ������ֵ
                // This pixel is already regarded as Background Pixel, then it has possibility of 1/�� to Run its model sample's value.
                int random = rng.uniform(0, random_sample);
                if (random == 0)
                {
                    random = rng.uniform(0, num_samples);
                    samples[i][j][random] = img.at<uchar>(i, j);
                }

                // ͬʱҲ�� 1 / �� �ĸ���ȥ���������ھӵ��ģ������ֵ
                // At the same time, it has possibility of 1/�� to Run its neighborhood point's sample value.
                random = rng.uniform(0, random_sample);
                if (random == 0)
                {
                    int row, col;
                    random = rng.uniform(0, 9); row = i + c_yoff[random];
                    random = rng.uniform(0, 9); col = j + c_xoff[random];

                    // ��ֹѡȡ�����ص�Խ��
                    // Protect Pixel from Crossing the border
                    if (row < 0) row = 0;
                    if (row >= img.rows)  row = img.rows - 1;
                    if (col < 0) col = 0;
                    if (col >= img.cols) col = img.cols - 1;

                    // Ϊ�����⸳���ֵ
                    // Set random pixel's Value for Sample Library
                    random = rng.uniform(0, num_samples);
                    samples[row][col][random] = img.at<uchar>(i, j);
                }
            }
        }
    }
}

/*===================================================================
 * ��������getFGModel
 * ˵������ȡǰ��ģ�Ͷ�ֵͼ��
 * ����ֵ��Mat
 *------------------------------------------------------------------
 * Function: getFGModel
 *
 * Summary:
 *   get Foreground Model Binary Image.
 *
 * Returns:
 *   Mat
=====================================================================
*/
Mat ViBe::getFGModel()
{
    return FGModel;
}

/*===================================================================
 * ��������deleteSamples
 * ˵����ɾ�������⣻
 * ����ֵ��void
 *------------------------------------------------------------------
 * Function: deleteSamples
 *
 * Summary:
 *   Delete Sample Library.
 *
 * Returns:
 *   void
=====================================================================
*/
void ViBe::deleteSamples()
{
    delete samples;
}
