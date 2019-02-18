/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>

#include<System.h>

#include<time.h>

using namespace std;

// From http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

int main(int argc, char **argv)
{
	string vocabPath = "../ORBvoc.txt";
	string settingsPath = "../webcam.yaml";
	string videoPath = "../video.avi";
	if (argc == 1)
	{

	}
	else if (argc == 2)
	{
		vocabPath = argv[1];
	}
	else if (argc == 3)
	{
		vocabPath = argv[1];
		settingsPath = argv[2];
	}
	else if (argc == 4)
	{
		vocabPath = argv[1];
		settingsPath = argv[2];
		videoPath = argv[3];
	}
    else
    {
        cerr << endl << "Usage: mono_webcam.exe path_to_vocabulary path_to_settings path_to_video" << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(vocabPath, settingsPath,ORB_SLAM2::System::MONOCULAR,true);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;

	cv::VideoCapture cap(videoPath);


	// From http://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
	__int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


	// Main loop
	cv::Mat im;
	cv::Mat Tcw;
    while (true)
    {
		cap.read(im);

		__int64 curNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		// Pass the image to the SLAM system
		Tcw = SLAM.TrackMonocular(im, curNow / 1000.0);

		// This will make a third window with the color images, you need to click on this then press any key to quit
		cv::imshow("Image", im);

		if (cv::waitKey(1) >= 0)
			break;
    }

    // Stop all threads
    SLAM.Shutdown();
	cap.release();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
}
