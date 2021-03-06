//
//  main_pose_error.cpp
//
//  Created by Sam Lyu on 2017-06-22.
//



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "cvxImage_310.hpp"
#include "cvxIO.hpp"
#include "cvxPoseEstimation.hpp"
#include "ms7ScenesUtil.hpp"
#include "dataset_param.h"

using namespace::std;

static void help()
{
    printf("need arguments Camera_pose .txt and predictions_list.txt \n");
}

int main(int argc, const char * argv[]){
	if(argc != 3 ){
		help();
		printf("parameter number is %d, should be 2. \n" , argc);
		return -1;
	
	}
	

	const char * camera_pose_file = argv[1];
	const char * prediction_pose_file = argv[2];



	
	
	vector<string> true_files  = Ms7ScenesUtil::read_file_names(camera_pose_file);
	vector<string> pred_files  = Ms7ScenesUtil::read_file_names(prediction_pose_file);
	vector<double> angle_errors;
        vector<double> translation_errors;
	ofstream error_file;
	error_file.open ("pose_error/error.txt");

	for (int k=0; k<pred_files.size(); k++){
	double angle_dis = 0.0;
	double location_dis = 0.0;

	string camera_file= true_files[k];
	string estimated_file= pred_files[k];
	cv::Mat tr_pose = Ms7ScenesUtil::read_pose_7_scenes(camera_file.c_str());
	cout<<"ture_pose"<<tr_pose<<endl;
	cv::Mat et_pose = Ms7ScenesUtil::read_pose_7_scenes(estimated_file.c_str());
 	cout<<"estimated_camera_pose"<<et_pose<<endl;
	CvxPoseEstimation::poseDistance(tr_pose, et_pose, angle_dis, location_dis);
        
	angle_errors.push_back(angle_dis);
        translation_errors.push_back(location_dis);
	printf("angle distance, location distance are %lf %lf\n", angle_dis, location_dis);
	error_file << angle_dis << "  " << location_dis << endl ;
	}//<< "angle distance " 
	
	double med_trans = 0.0;
	double med_agl = 0.0;
	
	//avg_trans= accumulate(translation_errors.begin(), translation_errors.end(),0.0)/translation_errors.size();
	//avg_agl= accumulate(angle_errors.begin(), angle_errors.end(),0.0)/angle_errors.size();

	sort(translation_errors.begin(), translation_errors.end());
	sort(angle_errors.begin(), angle_errors.end());
	med_trans = translation_errors[translation_errors.size()/2];
	med_agl= angle_errors[angle_errors.size()/2];
	
	printf("median angle distance, median location distance are %lf %lf\n", med_agl, med_trans);
	vector<double>::iterator it;
	int i=0;
	for(it=angle_errors.begin(); it < angle_errors.end(); it++,i++){
		if(*it>5){
			double percentage_agl= i/angle_errors.size();
			printf("%03d is the number of angle errors below 5 out of %03d \n",i,angle_errors.size());
			break;		
		}
	}

	vector<double>::iterator it1;
	int s=0;
	for(it1=translation_errors.begin(); it1 < translation_errors.end(); it1++,s++){
		if(*it1>0.05){
			
			printf("%03d is the number of transition errors below 0.05 out of %03d \n",s,translation_errors.size());
			break;		
		}
	}
	
	return 0;
	
}





