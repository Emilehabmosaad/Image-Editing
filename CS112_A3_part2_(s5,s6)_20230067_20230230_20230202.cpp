// File: CS112_A3_part2_(s5,s6)_20230067_20230230_20230202

// Porpose: A program that allows the user to perform Process on images

// Repo Link: 

/*
    Authors: 
        emil ehab mosaad (s5, s6), 
        Abdallah Mohamed Abdelmawgood (s5, s6),
        Abdulrahman Ahmed Kamal (s5, s6)
*/

/*
    Who did which filter: 
        emil ehab mosaad 20230067 (GrayScale (filter no.1), Lighten and Darken (filter no.7), Merge Images (filter no.4), Detect Image Edges (filter no.10)),
        Abdallah Mohamed Abdelmawgood 20230230 (Invert Image (filter no.3), Rotate Image (filter no.6), ِAdding a Frame to the Picture (filter no.9), Blur Images (filter no.12)),
        Abdulrahman Ahmed Kamal 20230202 (Black and White (filter no.2), Flip (filter no.5), Crop Image (filter no.8), Resize Image (filter no.11))
*/

/*
    Emails: 
        emil ehab mosaad (emilehab2@gmail.com),
        Abdallah Mohamed Abdelmawgood (abdullahmohamedabdelmawgood@gmail.com),
        Abdulrahman Ahmed Kamal (bedoa973@gmail.com)
*/



#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cctype>
#include "Image_Class.h"
using namespace std;
void MainMenu();

bool IsNumerical(string choice) 
{
    // Loop through each character in the string
    for (char c : choice) 
    {
        // Check if the character is alphabetic
        if (isalpha(c)) 
        {
            // If any character is alphabetic, return false
            return false; // The string contains at least one alphabetic character
        }
    }
    // If no alphabetic characters were found, return true
    return true; // The string contains only numerical characters
}

bool IsValidPath(const string& path) 
{
    // Check if the path exists and is a directory
    // Using filesystem::exists to check if the path exists
    // Using filesystem::is_directory to check if the path points to a directory
    return filesystem::exists(path) && filesystem::is_directory(path);
}

bool IsValidPostFex(const string& filename) 
{
    int i = 0;

    // Find the position of the dot (.) in the filename
    // Stop if a dot is found or if the end of the filename is reached
    while (i < filename.size() && filename[i] != '.') 
    {
        i++;
    }

    // If no dot (.) is found, return false
    if (i == filename.size()) 
    {
        return false;
    }

    // Extract the file extension (PostFix) from the filename
    string PostFix;
    for (int k = i + 1; k < filename.size(); ++k) 
    {
        // Convert each character to uppercase and append to PostFix
        PostFix += toupper(filename[k]);
    }

    // Check if the extracted file extension matches known image formats (JPEG, JPG, PNG, BMP)
    return (PostFix == "JPEG" || PostFix == "JPG" || PostFix == "PNG" || PostFix == "BMP");
}

string ReadInputFromUser() 
{
    string Input;

    // Prompt the user to enter an image name
    cout << "enter an image name: ";
    
    // Read the input from the user
    getline(cin, Input);

    // Validate the input: Check if it's a valid path or has a valid file extension
    while (!IsValidPath(Input) && !IsValidPostFex(Input)) 
    {
        // If input is not valid, prompt the user to enter a valid image name
        cout << "Invalid input, enter a valid image name: ";
        
        // Read the input from the user again
        getline(cin, Input);
    }

    // Return the validated input
    return Input;
}

int ReadchoiceFromUser(string message = "enter a number for your choice: ") 
{
    string Input;

    // Prompt the user to enter a number for their choice
    cout << message;

    // Read the input from the user
    getline(cin, Input);

    // Validate the input: Check if it's numerical
    while (!IsNumerical(Input)) 
    {
        // If input is not valid, prompt the user to enter a valid number
        cout << "Invalid input, enter a valid number: ";
        
        // Read the input from the user again
        getline(cin, Input);
    }

    // Convert the validated input to an integer and return it
    return stoi(Input);
}

void GrayScale(Image& image) 
{
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j) 
        {
            // Calculate the average intensity of the pixel across all channels
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) 
            {
                avg += image(i, j, k); // Accumulate intensity values
            }

            // Ensure that the average intensity does not exceed 255
            if (avg > 255) 
            {
                avg = 255;
            }

            // Set all channels of the pixel to the calculated average intensity
            for (int k = 0; k < image.channels; ++k) 
            {
                image(i, j , k) = avg; // Set intensity for each channel
            }
        }
    }
}

void Lighten(Image& image) 
{
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {
            for (int k = 0; k < image.channels; ++k) 
            {
                // Check if the pixel coordinates or channel index are out of bounds
                if (i < 0 || i >= image.width || j < 0 || j >= image.height || k < 0 || k >= image.channels) 
                {
                    continue; // Skip to the next iteration if out of bounds
                }

                // Calculate the new intensity after applying the lightening effect
                int new_intensity = image(i, j, k) + 0.5 * image(i, j, k);

                // Ensure that the new intensity does not exceed 255
                if (new_intensity > 255)
                {
                    image(i, j, k) = 255; // Set the intensity to the maximum value (255)
                    continue; // Skip to the next iteration
                }

                // Update the intensity of the pixel with the new value
                image(i, j, k) = new_intensity;
            }
        }
    }
}

void Darken(Image& image) {
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {
            for (int k = 0; k < image.channels; ++k) 
            {
                // Calculate the new intensity after applying the darkening effect
                int new_intensity = image(i, j, k) - 0.5 * image(i, j, k);

                // Ensure that the new intensity does not fall below 0
                if (new_intensity < 0) 
                {
                    image(i, j, k) = 0; // Set the intensity to the minimum value (0)
                    continue; // Skip to the next iteration
                }

                // Update the intensity of the pixel with the new value
                image(i, j, k) = new_intensity;
            }
        }
    }
}

void BlackAndWhite(Image& image) {
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {
            unsigned int avg = 0;

            // Calculate the average intensity across all channels
            for (int k = 0; k < 3; ++k) 
            { // Assuming 3 channels for RGB images
                avg += image(i, j, k);
            }
            avg /= 3; // Divide by the number of channels to get the average intensity

            // Set the threshold value for determining black or white
            unsigned int threshold_value = 128;

            // Determine whether the average intensity is below or above the threshold
            unsigned int new_intensity = (avg < threshold_value) ? 0 : 255;

            // Set all channels of the pixel to the determined intensity value
            for (int k = 0; k < 3; ++k) 
            { // Assuming 3 channels for RGB images
                image(i, j, k) = new_intensity;
            }
        }
    }
}

void HorizontalFlip(Image& image) 
{
    // Iterate over the left half of the image horizontally
    for (int i = 0; i < image.width / 2; ++i) 
    {
        // Iterate over all rows vertically
        for (int j = 0; j < image.height; ++j) 
        {
            // Iterate over each channel (assuming RGB format)
            for (int k = 0; k < 3; ++k) 
            {
                // Swap pixel values between left and right halves horizontally
                unsigned int temp = image(i, j, k); // Store current pixel value in temp variable
                image(i, j, k) = image(image.width - 1 - i, j, k); // Assign pixel value from right half to left half
                image(image.width - 1 - i, j, k) = temp; // Assign pixel value from temp variable to right half
            }
        }
    }
}

void VerticalFlip(Image& image) 
{
    // Iterate over each column of the image horizontally
    for (int i = 0; i < image.width; ++i) 
    {
        // Iterate over the top half of the image vertically
        for (int j = 0; j < image.height / 2; ++j) 
        {
            // Iterate over each channel (assuming RGB format)
            for (int k = 0; k < 3; ++k) 
            {
                // Swap pixel values between top and bottom halves vertically
                unsigned int temp = image(i, j, k); // Store current pixel value in temp variable
                image(i, j, k) = image(i, image.height - 1 - j, k); // Assign pixel value from bottom half to top half
                image(i, image.height - 1 - j, k) = temp; // Assign pixel value from temp variable to bottom half
            }
        }
    }
}

void InvertImage(Image& image) 
{
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {
            // Iterate over each channel of the pixel
            for (int k = 0; k < image.channels; ++k) 
            {
                // Invert the pixel value by subtracting it from 255
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

void Edge(Image& image1)
{
    BlackAndWhite(image1);

    for (int i = 0; i < image1.width; ++i)
    {
        for (int j = 0; j < image1.height; ++j)
        {
            // int avg1 = image1(i, j, 0) / 3 + image1(i, j, 1) / 3 + image1 (i, j, 2) / 3;
            // int avg2 = image1(i, j+1, 0) / 3 + image1(i, j+1, 1) / 3 + image1 (i, j+1, 2) / 3;
            if(j == image1.height - 1)
            {
                continue;
            }
            if(image1(i, j, 0) > image1(i + 1, j, 0) || image1(i, j, 0) < image1(i + 1, j, 0) || image1(i, j, 0) > image1(i, j + 1, 0) || 
                image1(i, j, 0) < image1(i, j + 1, 0) ||  image1(i, j, 0) < image1(i + 1, j + 1, 0) || image1(i, j, 0) > image1(i + 1, j + 1, 0)) 
            {
                
                image1(i, j, 0) = 0;
                image1(i, j, 1) = 0;
                image1(i, j, 2) = 0;
            }
            else
            {
                image1(i, j, 0) = 255;
                image1(i, j, 1) = 255;
                image1(i, j, 2) = 255;
            }
        }
    }
}

void Crop(Image& image, int startX, int startY, int cropWidth, int cropHeight) 
{
    // Check if the requested crop is within the boundaries of the original image
    if (startX + cropWidth > image.width || startY + cropHeight > image.height) 
    {
        cerr << "Crop dimensions exceed the boundaries of the original image." << endl;
        return;
    }

    // Create a new Image instance to hold the cropped area
    Image croppedImage(cropWidth, cropHeight);

    // Iterate over the crop area and copy pixels from the original image
    for (int i = startX; i < startX + cropWidth; i++) 
    {
        for (int j = startY; j < startY + cropHeight; j++) 
        {
            for (int k = 0; k < 3; k++) 
            { // Assuming 3 color channels (RGB)
                croppedImage(i - startX, j - startY, k) = image(i, j, k);
            }
        }
    }

    // Copy the cropped image data back to the original image
    image.width = cropWidth;
    image.height = cropHeight;
    delete[] image.imageData; // Free the previously allocated memory
    image.imageData = croppedImage.imageData;
    croppedImage.imageData = nullptr; // Prevent deallocation by croppedImage destructor
}

void Resize(Image& image, int new_Width, int new_Height) 
{
    Image resizedImage(new_Width, new_Height);

    double widthRatio = (double)new_Width / (double)image.width;
    double heightRatio = (double)new_Height / (double)image.height;

    for (int i = 0; i < new_Width; i++) 
    {
        for (int j = 0; j < new_Height; j++) 
        {
            for (int k = 0; k < 3; k++) 
            { 
                
                int originalX = static_cast<int>(i / widthRatio);
                int originalY = static_cast<int>(j / heightRatio);               
                resizedImage(i, j, k) = image(originalX, originalY, k);
            }
        }
    }

    // Copy the cropped image data back to the original image
    image.width = new_Width;
    image.height = new_Height;
    delete[] image.imageData; // Free the previously allocated memory
    image.imageData = resizedImage.imageData;
    resizedImage.imageData = nullptr; // Prevent deallocation by croppedImage destructor
}

void MargeTwoImages(Image& image1)
{
    string ImageName;
    Image image2;
    bool validImageLoaded = false;

    // Loop until a valid image is loaded
    while (!validImageLoaded) 
    {
        // Read input for image name
        ImageName = ReadInputFromUser();
        try 
        {
            // Attempt to load the image
            image2.loadNewImage(ImageName);
            validImageLoaded = true;
        } 
        catch (exception &e) 
        {
            // Display error if image loading fails
            cerr << "Image doesn't exist" << endl;
        }
    }

    if(image2.width != image1.width || image2.height != image1.height)
    {
        Resize(image2, image1.width, image1.height);

        for (int i = 0; i < image1.width; ++i)
        {
            for (int j = 0; j < image1.height; ++j)
            {
                for (int k = 0; k < image1.channels; ++k)
                {
                    image1(i, j, k) = 0.5 * image1(i, j, k) + 0.5 * image2(i, j, k);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < image1.width; ++i)
        {
            for (int j = 0; j < image1.height; ++j)
            {
                for (int k = 0; k < image1.channels; ++k)
                {
                    image1(i, j, k) = 0.5 * image1(i, j, k) + 0.5 * image2(i, j, k);
                }
            }
        }
    }
}

void RotateImage(Image& image1, int angel)
{

    if (angel == 180)
    {
        Image rotated_image(image1.width,image1.height);
        for (int i = 0; i < image1.width; ++i)
        {
            for (int j = 0; j < image1.height; ++j)
            {
                for (int k = 0; k < image1.channels; ++k)
                {
                    rotated_image(image1.width-1-i,image1.height-1-j,k) =image1(i, j, k);
                }
            }
        }
        // Copy the cropped image data back to the original image
        image1.width = rotated_image.width;
        image1.height = rotated_image.height;
        delete[] image1.imageData; // Free the previously allocated memory
        image1.imageData = rotated_image.imageData;
        rotated_image.imageData = nullptr; // Prevent deallocation by croppedImage destructor
    }
    else if (angel == 270)
    {
        Image rotated_image(image1.height,image1.width);
        for (int i = 0; i < image1.width; ++i)
        {
            for (int j = 0; j < image1.height; ++j)
            {
                for (int k = 0; k < image1.channels; ++k)
                {
                    rotated_image(j,image1.width-1-i, k) = image1(i, j, k);
                }
            }
        }
        // Copy the cropped image data back to the original image
        image1.width = rotated_image.width;
        image1.height = rotated_image.height;
        delete[] image1.imageData; // Free the previously allocated memory
        image1.imageData = rotated_image.imageData;
        rotated_image.imageData = nullptr; // Prevent deallocation by croppedImage destructor
    }
    else if (angel== 90)
    {
        Image rotated_image( image1.height,image1.width);
        for (int i = 0; i < image1.width; ++i)
        {
            for (int j = 0; j < image1.height; ++j)
            {
                for (int k = 0; k < image1.channels; ++k)
                {
                    rotated_image(image1.height-1-j,i, k) = image1(i, j, k);
                }
            }
        }
        // Copy the cropped image data back to the original image
        image1.width = rotated_image.width;
        image1.height = rotated_image.height;
        delete[] image1.imageData; // Free the previously allocated memory
        image1.imageData = rotated_image.imageData;
        rotated_image.imageData = nullptr; // Prevent deallocation by croppedImage destructor
    }
}

void BlurImage(Image& image)
{
    Image blurredimage(image.width,image.height);

    int blurdeg = 10;

    for (int i = 0; i<image.width; i++)
    {
        for (int j = 0; j<image.height; ++j)
        {
            for (int k = 0; k<3; ++k)
            {
                int sum = 0;
                int count = 0;

                for (int nx = i-blurdeg; nx <= i+blurdeg; ++nx)
                {
                    for (int ny = j-blurdeg; ny <= j+blurdeg; ++ny)
                    {
                        if (nx>= 0 && nx < image.width && ny >= 0 && ny < image.height)
                        {
                            sum += image(nx, ny, k);    count++;
                        }
                    }
                }
                blurredimage(i, j, k) = sum/count;
            }
        }
    }
    
    // Copy the cropped image data back to the original image
    image.width = blurredimage.width;
    image.height = blurredimage.height;
    delete[] image.imageData; // Free the previously allocated memory
    image.imageData = blurredimage.imageData;
    blurredimage.imageData = nullptr; // Prevent deallocation by croppedImage destructor
}

void SimpleFrame(Image& image) 
{
    int framewidth=100;

    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            if (i<framewidth||i>image.width-framewidth||j<framewidth||j>image.height-framewidth) 
            {
                for (int k = 0; k < image.channels; k++) 
                {
                    image.setPixel(i, j,k,255);
                }
            }
        }
    }
}

void FancyFrame(Image& image) 
{
    int framewidth =70;
    int secframe =70;
    int thiframe =70;

    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            if (i<framewidth||i>image.width-framewidth||j<framewidth||j>image.height-framewidth) 
            {
                for (int k = 0; k < image.channels; k++) 
                {
                    image.setPixel(i, j, k, 0);
                }
            }
        }
    }
    
    for (int i = framewidth; i < image.width - framewidth; i++) 
    {
        for (int j = framewidth; j < image.height - framewidth; j++) 
        {
            if (i<framewidth+secframe||i>image.width-framewidth-secframe||j<framewidth+secframe||j> image.height-framewidth-secframe) 
            {
                for (int k = 0; k < image.channels; k++) 
                {
                    image.setPixel(i, j, k, 255);
                }
            }
        }
    }

    for (int i = framewidth+secframe; i < image.width-framewidth-secframe; i++) 
    {
        for (int j = framewidth+secframe; j < image.height-framewidth-secframe; j++) 
        {
            if (i<framewidth+secframe+thiframe||i>image.width-framewidth-secframe-thiframe||j<framewidth+secframe+thiframe||j>image.height-framewidth-secframe-thiframe)  
            {
                for (int k = 0; k < image.channels; k++) 
                {
                    image.setPixel(i, j, 2, 255); 
                }
            }
        }
    }
}

int FiltersMenu() 
{
    // Display the menu options
    cout << "==========================================" << endl;
    cout << "[1] GrayScale" << endl;
    cout << "[2] Black and White" << endl;
    cout << "[3] Darken and Lighten Image" << endl;
    cout << "[4] Flip Image" << endl;
    cout << "[5] Invert Image" << endl;
    cout << "[6] Draw Edge" << endl;
    cout << "[7] Crop Image" << endl;
    cout << "[8] Resize Image" << endl;
    cout << "[9] Marge Two Images" << endl;
    cout << "[10] Rotate Image" << endl;
    cout << "[11] Blur Image" << endl;
    cout << "[12] Add Simple Frame" << endl;
    cout << "[13] Add Fancy Frame" << endl;
    cout << "[14] Back" << endl;
    cout << "==========================================" << endl;

    int choice;

    // Read the user's choice from input
    choice = ReadchoiceFromUser();

    return choice;
}

int SaveMenu() 
{
    // Display the menu options
    cout << "==========================================" << endl;
    cout << "[1] Apply a filter and Save it" << endl;
    cout << "[2] Back" << endl;
    cout << "==========================================" << endl;

    // Read the user's choice from input
    int choice = ReadchoiceFromUser();

    return choice; // Return the user's choice
}

bool MoveImage(const filesystem::path& source, const filesystem::path& destination)
{
    // Open the source file for reading in binary mode
    ifstream sourceFile(source, ios::binary);
    if (!sourceFile.is_open()) 
    {
        cerr << "Error: Unable to open source image file." << endl;
        return false;
    }

    // Open the destination file for writing in binary mode
    ofstream destinationFile(destination, ios::binary);
    if (!destinationFile.is_open()) 
    {
        cerr << "Error: Unable to open destination image file." << endl;
        return false;
    }

    // Copy the contents of the source file to the destination file
    destinationFile << sourceFile.rdbuf();

    // Close both files
    sourceFile.close();
    destinationFile.close();

    // Check if the destination file was created successfully
    if (!destinationFile) 
    {
        cerr << "Error: Unable to copy image file contents." << endl;
        return false;
    }

    return true;
}

void saveImage(Image& image)
{
    // Prompt user for file name and save the image
    string SavedImageName = ReadInputFromUser();

    // Handle user's save preferences
    char check = 'z';
    while(check != 'n' && check != 'N' && check != 'y' && check != 'Y')
    {
        cout << "Do you want save here (Y/N),(y/n): ";
        cin >> check;
    }

    cin.ignore();

    // check == "y" -> save the image in current path
    if(check == 'y' || check == 'Y')
    {
        if (image.saveImage(SavedImageName))
        {
            cout << "saved successfully. " << endl;
        }
    }
    else
    { // check != "y" 
        string path = " ";
        
        // Read a valid path 
        while(!IsValidPath(path))
        {
            cout << "enter a path: ";
            getline(cin, path);
        }

        
        try
        { // Save image and copy it in user's path
            image.saveImage(SavedImageName);
            filesystem::path DestinationPath = path + "\\" + SavedImageName;
            filesystem::path ImagePath = filesystem::current_path().string() + "\\" + SavedImageName;
            bool is = MoveImage(ImagePath, DestinationPath);
            if(is)
            {
                cout << "saved successfully. " << endl; 

                // remove image what in current path
                filesystem::remove(ImagePath);
            }
        }
        catch(const exception& e)
        {
            // Print error if save operation failed
            cerr << e.what() << endl;
        }
    }
}

void darkenOrLighten(Image &image) {
    int choice;
    cout << "==========================================" << endl;
    cout << "[1] Darken" << endl;
    cout << "[2] Lighten" << endl;
    cout << "==========================================" << endl;

    choice = ReadchoiceFromUser();
    if (choice == 1)
        Darken(image);
    else if (choice == 2)
        Lighten(image);
    else
    {
        cout << "Invalid choice" << endl;
        darkenOrLighten(image);
    }
}

void horizontalOrVerticalFlip(Image &image) 
{
    int choice;

    cout << "==========================================" << endl;
    cout << "[1] Horizontal" << endl;
    cout << "[2] Vertical" << endl;
    cout << "==========================================" << endl;

    choice = ReadchoiceFromUser();
    if (choice == 1)
        HorizontalFlip(image);
    else if (choice == 2)
        VerticalFlip(image);
    else
    {
        cout << "Invalid choice" << endl;
        horizontalOrVerticalFlip(image);
    }
}

void applyFilterAndSave(Image &image) 
{
    int Filterchoice = FiltersMenu();

    switch (Filterchoice) 
    {
        case 1:
            GrayScale(image);
            break;
        case 2:
            BlackAndWhite(image);
            break;
        case 3:
            darkenOrLighten(image);
            break;
        case 4:
            horizontalOrVerticalFlip(image);
            break;
        case 5:
            InvertImage(image);
            break;
        case 6:
            Edge(image);
            break;
        case 7:
            Crop(image, ReadchoiceFromUser("Enter the starting X coordinate for the crop: "), 
                ReadchoiceFromUser("Enter the starting Y coordinate for the crop: "), ReadchoiceFromUser("Enter the width for the crop: "), 
                ReadchoiceFromUser("Enter the height for the crop: "));
            break;
        case 8:
            Resize(image, ReadchoiceFromUser("Enter new width for the image: "), ReadchoiceFromUser("Enter the new height for the image"));
            break;
        case 9:
            MargeTwoImages(image);
            break;
        case 10:
            RotateImage(image, ReadchoiceFromUser("Enter a Degree to Rotate (90, 180, 270): "));
            break;
        case 11:
            BlurImage(image);
            break;
        case 12:
            SimpleFrame(image);
            break;
        case 13:
            FancyFrame(image);
            break;
        case 14:
            return;
        default:
        {
            cout << "Invalid choice" << endl;
            applyFilterAndSave(image);
            break;
        }
    }

    // check if user want to apply new filter in image
    char check = 'z';

    while(check != 'n' && check != 'N' && check != 'y' && check != 'Y')
    {
        cout << "apply one more filter (n/y), (N/Y): ";
        cin >> check;
    }

    cin.ignore();

    if(check == 'Y' || check == 'y')
    {
        applyFilterAndSave(image);
        return;
    }

    // Prompt user for save option
    int Savechoice = SaveMenu();
    if (Savechoice == 1)
        saveImage(image);

}

void MainMenu() 
{
    // Display main menu options
    cout << "==========================================" << endl;
    cout << "[1] Load a new image" << endl;
    cout << "[2] Exit" << endl;
    cout << "==========================================" << endl;

    // Read user's choice
    int choice = ReadchoiceFromUser();

    // Handle user's choice
    switch (choice) {
        // Case for loading a new image
        case 1: 
        {
            string ImageName;
            Image image;
            bool validImageLoaded = false;

            // Loop until a valid image is loaded
            while (!validImageLoaded) 
            {
                // Read input for image name
                ImageName = ReadInputFromUser();
                try 
                {
                    // Attempt to load the image
                    image.loadNewImage(ImageName);
                    validImageLoaded = true;
                } 
                catch (exception &e) 
                {
                    // Display error if image loading fails
                    cerr << "Image doesn't exist" << endl;
                }
            }
            // apply filter
            applyFilterAndSave(image);
            break;
        }
        // Case for exiting the program
        case 2:
            return; // Exit the program

        // Default case for invalid choice
        default:
            cout << "Invalid choice" << endl;
    }

    MainMenu(); // Restart the main menu
}

int main()
{
    // call main menu function
    MainMenu();

    return 0;
}