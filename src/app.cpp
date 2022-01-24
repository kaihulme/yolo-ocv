#include <app.h>

#define IMG_WIDTH 416 
#define IMG_HEIGHT 416

#define CONF_THR 0.5 // threshold for detection confidence
#define NMS_THR 0.4 // threshold for non-maximum supression

using namespace std;
using namespace cv;
using namespace dnn;

int main(void) {

	vector<string> coco_classes;
	ifstream coco_file("resources/coco/coco.names");
	string line;
	while(getline(coco_file, line)) {
		coco_classes.push_back(line);
	}

	const string yolo_conf = "resources/yolo/yolov3.cfg";
	const string yolo_weights = "resources/yolo/yolov3.weights";
	Net net = readNetFromDarknet(yolo_conf, yolo_weights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	Mat blob;
	Mat img = imread("bird.jpg");
	blobFromImage(img, blob, 1/255.0, Size(IMG_WIDTH, IMG_HEIGHT), Scalar(0, 0, 0), true, false);
	
	net.setInput(blob);

	vector<Mat> outputs;

	net.forward(outputs, net.getUnconnectedOutLayersNames());

	vector<int> classes;
	vector<float> confidences;
	vector<Rect> boxes;

	for (Mat output : outputs) {
		for (int i; i<output.rows; i++) {

			Mat scores = output.row(i).colRange(5, output.cols);
			
			double max_conf;
			Point max_pos;
			minMaxLoc(scores, 0, &max_conf, 0, &max_pos);

			if (max_conf > CONF_THR) {

				int box_x = (int)((output.at<float>(i, 0) * IMG_WIDTH) - IMG_WIDTH / 2);
				int box_y = (int)((output.at<float>(i, 1) * IMG_HEIGHT) - IMG_HEIGHT / 2);
				int box_w = (int)(output.at<float>(i, 2) * IMG_WIDTH);
				int box_h = (int)(output.at<float>(i, 3) * IMG_HEIGHT);
				Rect box = Rect(box_x, box_y, box_w, box_h);

				classes.push_back(max_pos.x);
				confidences.push_back(max_conf);
				boxes.push_back(box);

			}

		}
	}

	vector<Rect> final_boxes;
	vector<int> box_idxs;
	NMSBoxes(boxes, confidences, CONF_THR, NMS_THR, box_idxs);
	for (int idx : box_idxs) final_boxes.push_back(boxes[idx]);

	

	return 0;
}
