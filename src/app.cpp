#include <app.h>

#define IN_WIDTH 416 
#define IN_HEIGHT 416
#define CONF_THR 0.5
#define NMS_THR 0.4 

using namespace std;
using namespace cv;
using namespace dnn;

int main(void) {

	// get image as blob
	Mat blob;
	Mat img = imread("bird.jpg");
	blobFromImage(img, blob, 1/255.0, Size(IN_WIDTH, IN_HEIGHT), Scalar(0, 0, 0), true, false);

	// build network from config & weights and set input
	const string yolo_conf = "resources/yolo/yolov3.cfg";
	const string yolo_weights = "resources/yolo/yolov3.weights";
	Net net = readNetFromDarknet(yolo_conf, yolo_weights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);
	net.setInput(blob);

	// forward pass of network
	vector<Mat> outputs;
	net.forward(outputs, net.getUnconnectedOutLayersNames());

	// find bounding boxes that meet confidence threshold
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
				int box_x = (int)(output.at<float>(i, 0) * img.cols);
				int box_y = (int)(output.at<float>(i, 1) * img.rows);
				int box_w = (int)(output.at<float>(i, 2) * img.cols);
				int box_h = (int)(output.at<float>(i, 3) * img.rows);
				box_x = box_x - box_w / 2;
				box_y = box_y - box_h / 2;
				Rect box = Rect(box_x, box_y, box_w, box_h);
				classes.push_back(max_pos.x);
				confidences.push_back(max_conf);
				boxes.push_back(box);
			}
		}
	}

	// apply non-maximum supression to boxes
	vector<Rect> final_boxes;
	vector<int> box_idxs;
	NMSBoxes(boxes, confidences, CONF_THR, NMS_THR, box_idxs);
	for (int idx : box_idxs) final_boxes.push_back(boxes[idx]);

	// get class names from COCO dataset
	// vector<string> coco_classes;
	// ifstream coco_file("resources/coco/coco.names");
	// string line;
	// while(getline(coco_file, line)) coco_classes.push_back(line);

	// draw predictions on image
	for (Rect box : final_boxes) {
		rectangle(img, box, Scalar(0, 255, 0));
		cout << box << endl;
	}

	imwrite("out/output.jpg", img);

	cout << final_boxes.size() << endl;

	return 0;
}
