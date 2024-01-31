% Define file paths
originalImageFile = 'test1.png'; 
equalizedImageFile = 'test1_output_equalized.png'; 
originalHistogramFile = 'test1_output_original_histogram.csv'; 
equalizedHistogramFile = 'test1_output_equalized_histogram.csv'; 

% Read and display the original image
originalImage = imread(originalImageFile);
figure('Name', 'Original Image');
imshow(originalImage);
title('Original Image');
print('Original_Image', '-dpng'); % Save the figure

% Read the original histogram data from the CSV file
originalHistogramData = csvread(originalHistogramFile);

% Plot the original histogram as a bar graph
figure('Name', 'Histogram of Original Image');
bar(originalHistogramData(:, 1), originalHistogramData(:, 2:4), 'grouped');
title('Histogram of Original Image');
xlabel('Intensity Value');
ylabel('Pixel Count');
legend('Red Channel', 'Green Channel', 'Blue Channel');
ylim([0 max(max(originalHistogramData(:, 2:4)))]); % Set the y-axis to start at 0
print('Histogram_Original_Image', '-dpng'); % Save the figure

% Read and display the equalized image
equalizedImage = imread(equalizedImageFile);
figure('Name', 'Equalized  Image');
imshow(equalizedImage);
title('Equalized  Image');
print('Equalized_Image', '-dpng'); % Save the figure

% Read the equalized histogram data from the CSV file
equalizedHistogramData = csvread(equalizedHistogramFile);
% Plot the equalized histogram as a bar graph
figure('Name', 'Histogram of Equalized Image');
bar(equalizedHistogramData(:, 1), equalizedHistogramData(:, 2:4), 'grouped');
title('Histogram of Equalized  Image');
xlabel('Intensity Value');
ylabel('Pixel Count');
legend('Red Channel', 'Green Channel', 'Blue Channel');
ylim([0 max(max(equalizedHistogramData(:, 2:4)))]); % Set the y-axis to start at 0
print('Histogram_Equalized_Image', '-dpng'); % Save the figure
