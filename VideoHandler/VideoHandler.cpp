#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::string inputVideoPath = "C:/Projects/ПеленгЗадачи/VideoHandler/testVideos/start_video2.mp4";  // Путь к исходному видеофайлу
    std::string outputVideoPath = "C:/Projects/ПеленгЗадачи/VideoHandler/testVideos/end_video2.mp4";  // Путь к выходному видеофайлу

    cv::VideoCapture cap(inputVideoPath);
    if (!cap.isOpened())
        return -1;

    cv::VideoWriter writer;
    int codec = cv::VideoWriter::fourcc('M', 'P', '4', '2');
    double fps = 25.0;
    cv::Size frame_size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    writer.open(outputVideoPath, codec, fps, frame_size, true);

    if (!writer.isOpened())
    {
        std::cout << "Could not open the output video file for write\n";
        return -1;
    }

    cv::namedWindow("Video", 1);
    for (;;)
    {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        int frame_number = cap.get(cv::CAP_PROP_POS_FRAMES);
        int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        int codec = cap.get(cv::CAP_PROP_FOURCC);

        std::stringstream ss_frame;
        ss_frame << "Frame: " << frame_number;
        cv::putText(frame, ss_frame.str(), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
        std::stringstream ss_resolution;
        ss_resolution << "Resolution: " << frame_width << "x" << frame_height;
        cv::putText(frame, ss_resolution.str(), cv::Point(10, 50), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
        std::stringstream ss_codec;
        ss_codec << "Codec: " << codec;
        cv::putText(frame, ss_codec.str(), cv::Point(10, 70), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);


        cv::imshow("Video", frame);
        writer.write(frame);
        if (cv::waitKey(30) >= 0) break;
    }
    return 0;
}
