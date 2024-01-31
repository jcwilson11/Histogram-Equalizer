#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Terminal command. SHould print .csv files for original and equalized image, as well as the images themselves in the folder's directory
// & ".\Joris Wilson F23 CPE462 Final Project.exe" test1.png test1_output 512 512, or "Joris Wilson F23 CPE462 Final Project.exe" test1.png test1_output 512 512

// Function to calculate the histogram for color images
// https://docs.opencv.org/4.x/d1/db7/tutorial_py_histogram_begins.html
// https://www.tutorialspoint.com/how-to-split-images-into-different-channels-in-opencv-using-cplusplus
void calculateColorHistogram(const cv::Mat& image, std::vector<cv::Mat>& histograms) {
    // Split the image into its respective color channels
    cv::Mat bgr[3];
    cv::split(image, bgr);

    // Set the number of bins and the range of values
    int numBins = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };

    // Calculate the histogram for each channel
    for (int i = 0; i < 3; ++i) {
        cv::calcHist(&bgr[i], 1, 0, cv::Mat(), histograms[i], 1, &numBins, &histRange, true, false);
        cv::normalize(histograms[i], histograms[i], 0, image.rows, cv::NORM_MINMAX, -1, cv::Mat());
    }
}

// Function to save the histogram to a CSV file
// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/#:~:text=URL%3A%20https%3A%2F%2Fwww.gormanalysis.com%2Fblog%2Freading
void saveHistogramToCSV(const std::vector<cv::Mat>& histograms, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (int i = 0; i < histograms[0].rows; ++i) {
            outputFile << i;
            for (int j = 0; j < histograms.size(); ++j) {
                outputFile << "," << histograms[j].at<float>(i);
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
    else {
        std::cerr << "Could not open " << filename << " for writing." << std::endl;
    }
}

// How to load file in terminal
// https://docs.opencv.org/3.4/d4/d1b/tutorial_histogram_equalization.html#:~:text=URL%3A%20https%3A%2F%2Fdocs
int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Usage: " << argv[0] << " <InputImage> <OutputImagePrefix> <Width> <Height>" << std::endl;
        return -1;
    }

    std::string inputImageFile = argv[1];
    std::string outputImagePrefix = argv[2];

    // Load the image
    cv::Mat originalImage = cv::imread(inputImageFile);
    if (originalImage.empty()) {
        std::cout << "Could not open or find the image." << std::endl;
        return -1;
    }

    // Vector to hold the histograms for the original image
    std::vector<cv::Mat> originalHistograms(3);
    calculateColorHistogram(originalImage, originalHistograms);
    saveHistogramToCSV(originalHistograms, outputImagePrefix + "_original_histogram.csv");

    // Equalize the histogram for the color image
    cv::Mat equalizedImage;
    cv::Mat ycrcb;

    // Convert the image from BGR to YCrCb color space
    cv::cvtColor(originalImage, ycrcb, cv::COLOR_BGR2YCrCb);

    // Split the image into channels
    std::vector<cv::Mat> channels;
    cv::split(ycrcb, channels);

    // Equalize the histogram of the Y channel
    cv::equalizeHist(channels[0], channels[0]);

    // Merge the channels back and convert to BGR color space
    cv::merge(channels, ycrcb);
    cv::cvtColor(ycrcb, equalizedImage, cv::COLOR_YCrCb2BGR);

    // Save the equalized image
    cv::imwrite(outputImagePrefix + "_equalized.png", equalizedImage);

    // Vector to hold the histograms for the equalized image
    std::vector<cv::Mat> equalizedHistograms(3);
    calculateColorHistogram(equalizedImage, equalizedHistograms);
    saveHistogramToCSV(equalizedHistograms, outputImagePrefix + "_equalized_histogram.csv");

    std::cout << "Histograms computed and saved successfully." << std::endl;
    return 0;
}
