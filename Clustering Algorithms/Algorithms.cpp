#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <cmath>
using namespace cv;
using namespace std;

/// <summary>
/// FUNCTION NAME: removeDuplicate
/// Description: Removes duplicates of int duplicate and replaces all instances with Replace parameter in the array.
/// Usage : TASK1
/// </summary>
void removeDuplicate(int ** &arr, int row, int col, int duplicate,int replace) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (arr[r][c] == duplicate) {
                arr[r][c] = replace;
            }
        }
    }
}

/// <summary>
/// FUNCTION NAME: FindDuplicate
/// Desscription: Finds collisions in the connected components labelling
/// Usage: TASK1
/// </summary>
void findDuplicate(int **  &arr, int row, int col) {
    for (int r = 1; r < row; r++) {
        for (int c = 1; c < col; c++) {
            if (arr[r][c] != 0) {
                if (arr[r][c] != arr[r][c - 1] && arr[r][c-1]!=0) {
                    removeDuplicate(arr,row,col,arr[r][c],arr[r][c-1]);
                }
                if (arr[r][c] != arr[r - 1][c - 1] && arr[r-1][c-1]!=0) {
                    removeDuplicate(arr, row, col, arr[r][c], arr[r-1][c - 1]);
                }
                if (arr[r][c] != arr[r - 1][c] && arr[r-1][c]!=0) {
                    removeDuplicate(arr, row, col, arr[r][c], arr[r - 1][c]);
                }
                if (arr[r][c] != arr[r - 1][c + 1] && arr[r-1][c+1]!=0) {
                    removeDuplicate(arr, row, col, arr[r][c], arr[r - 1][c + 1]);
                }
            }
        }
    }

}

/// <summary>
/// FUNCTION NAME: LABELMAKERS
/// Description: ASSIGNS LABEL TO ELEMEBTS THROUGH CONNECTED COMPONENTS LABELLING.
/// Usage: TASK1
/// </summary>
void LabelMaker(int ** &arr, int rows, int cols,int &labelCounter) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (arr[r][c] == 255) {
                switch (r) {
                case 0:
                    if (r == 0) {
                        labelCounter++;
                        arr[r][c] = labelCounter;
                    }
                    else {
                        if (arr[r][c - 1] == 0) {
                            labelCounter++;
                            arr[r][c] = labelCounter;
                        }
                        else {
                            arr[r][c] = arr[r][c - 1];
                        }
                    }
                    break;
                default:
                    if (c == 0) {
                        if (arr[r - 1][c + 1] == 0 && arr[r - 1][c] == 0) {
                            arr[r][c] == 0;
                        }
                        if (arr[r - 1][c + 1] == arr[r - 1][c]) {
                            arr[r][c] = arr[r - 1][c + 1];
                        }
                    }
                    else {
                        if (c != cols - 1) {
                            if ((arr[r - 1][c - 1] == 0) && (arr[r - 1][c] == 0) && (arr[r - 1][c + 1] == 0) && (arr[r][c - 1] == 0)) {
                                labelCounter++;
                                arr[r][c] = labelCounter;
                            }
                            if (arr[r - 1][c - 1] != 0 && arr[r - 1][c - 1] == arr[r - 1][c] && arr[r - 1][c - 1] == arr[r - 1][c + 1] && arr[r - 1][c - 1] == arr[r][c - 1]) {
                                arr[r][c] = arr[r - 1][c - 1];
                            }
                            else {
                                if (arr[r - 1][c - 1] != 0) {
                                    arr[r][c] = arr[r - 1][c - 1];
                                }
                                if (arr[r - 1][c] != 0) {
                                    arr[r][c] = arr[r - 1][c];
                                }
                                if (arr[r - 1][c + 1] != 0) {
                                    arr[r][c] = arr[r - 1][c + 1];
                                }
                                if (arr[r][c - 1] != 0) {
                                    arr[r][c] = arr[r][c - 1];
                                }
                            }
                        }
                        else {
                            if ((arr[r - 1][c - 1] == 0) && (arr[r - 1][c] == 0) && (arr[r][c - 1] == 0)) {
                                labelCounter++;
                                arr[r][c] = labelCounter;
                            }
                            if (arr[r - 1][c - 1] != 0 && arr[r - 1][c - 1] == arr[r - 1][c] && arr[r - 1][c - 1] == arr[r][c - 1]) {
                                arr[r][c] = arr[r - 1][c - 1];
                            }
                            else {
                                if (arr[r - 1][c - 1] != 0) {
                                    arr[r][c] = arr[r - 1][c - 1];
                                }
                                if (arr[r - 1][c] != 0) {
                                    arr[r][c] = arr[r - 1][c];
                                }
                                if (arr[r][c - 1] != 0) {
                                    arr[r][c] = arr[r][c - 1];
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }


}

/// <summary>
/// FUNCTION NAME: Make2D
/// Description: Makes a new 2D array (dynamically) of type t (int,char,Vec3b etc.)
/// Usage: Task1 & Task2
/// </summary>
template <typename t>
void Make2D(t** & arr, int rows, int cols) {
    arr = new t*[rows];
    for (int r = 0; r < rows; r++) {
        arr[r] = new t[cols];
    }
}

/// <summary>
/// FUNCTION NAME: Delete2D
/// Description: Deletes a 2D array of type D (int,char,Vec3b etc.)
/// Usage: Task1 & Task2
/// </summary>
template <typename D>
void Delete2D(D** &arr, int row=572) {
    for (int r = 0; r < row; r++) {
        delete[] arr[r];
        arr[r] = NULL;
    }
    delete[] arr;
    arr = NULL;
}

/// <summary>
/// Structure Name: Cluster
/// Description: Holds the centeroid Value of the cluster. Has overloaded functions for comparison of two centeroids.
/// Usage: Task2
/// </summary>
struct Cluster {
    int x, y, z; // Correspond centeroid Value
    Cluster() :x(0), y(0), z(0) {

    }
    void operator=(Cluster & other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    bool operator>(Cluster& other) {
        double avgthis, avgother;
        avgthis = (x + y + z);
        avgother = (other.x + other.y + other.z);

        if (avgthis >= avgother)
            return true; // greater intensity

        return false;
        
    }
    void display() {
        cout << "Values =  " << x << " " << y << " " << z << endl;
    }
};

/// <summary>
/// Function Name:AssignRandomClusters
/// Description: uses Rand() function to assign values to both the clusters. To speed things up, rand values calculate
///              the rows and column component and give it value from the given dataset. 
/// Usage: Task2
/// </summary>
void AssignRandomClusters(Cluster &k1, Cluster &k2, int rows, int cols, Mat & img) {
    unsigned int parameter = time(0);
    srand(parameter);

    int r1 = rand()%rows;
    int c1 = rand()%cols; // using random values from the data set to find clusters quicker
    int r2 = rand()%rows;
    int c2 = rand()%cols;

    

    k1.x = img.at<Vec3b>(r1,c1)[0];
    k1.y = img.at<Vec3b>(r1,c1)[1];
    k1.z = img.at<Vec3b>(r1,c1)[2];

    k2.x = img.at<Vec3b>(r2, c2)[0];
    k2.y = img.at<Vec3b>(r2, c2)[1];
    k2.z = img.at<Vec3b>(r2, c2)[2];

}

/// <summary>
/// Function Name: ComputeNewCenteroids
/// Description : Checks all the values of the 2D array and sees their corresponding clusters. The new average(centeroid) of 
///               both the clusters is then computed.
/// Usage: Task2
/// </summary>
void ComputeNewCenteroids(Cluster&k1,Cluster&k2,int rows,int cols, string** &decider, Vec3b ** &values) {
    int k1Counter = 0,k2Counter=0;
    Cluster k1Avg,k2Avg;
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (strcmp(decider[r][c].c_str(), "c1") == 0) {
                k1Avg.x += values[r][c][0];
                k1Avg.y += values[r][c][1];
                k1Avg.z += values[r][c][2];
                k1Counter++;
            }
            else {
                k2Avg.x += values[r][c][0];
                k2Avg.y += values[r][c][1];
                k2Avg.z += values[r][c][2];
                k2Counter++;
            }
        }
    }

    k1Avg.x = k1Avg.x / k1Counter;
    k1Avg.y = k1Avg.y / k1Counter;
    k1Avg.z = k1Avg.z / k1Counter;

    k2Avg.x = k2Avg.x / k2Counter;
    k2Avg.y = k2Avg.y / k2Counter;
    k2Avg.z = k2Avg.z / k2Counter;

    k1 = k1Avg;
    k2 = k2Avg;

}


/// <summary>
/// Function Name: DecideCluster
/// Description : Takes in the value passed and decides which cluster, the value belongs to. The value of corresponding decider
///               is then updated upon checking which clusters centeroid is closer to the passed value.
/// Usage : Task2
/// </summary>
void DecideCluster(Vec3b &value, Cluster &k1, Cluster &k2, string &decider, bool &updates, int type) {
    double d1, d2;// distance from cluster1 (d1), distance from cluster2 (d2)
    Cluster temp1, temp2;

    
        temp1.x = pow((k1.x - value[0]), 2);
        temp1.y = pow((k1.y - value[1]), 2);
        temp1.z = pow((k1.z - value[2]), 2);
        d1 = pow((temp1.x + temp1.y + temp1.z), double(0.5)); // distance calculation in 3 Dimensions

        temp2.x = pow((k2.x - value[0]), 2);
        temp2.y = pow((k2.y - value[1]), 2);
        temp2.z = pow((k2.z - value[2]), 2);
        d2 = pow((temp2.x + temp2.y + temp2.z), double(0.5));   // distance calculation in 3 Dimensions

    if (type == 1) {
        updates = true;
        if (d1 <= d2) 
            decider = "c1";    
        else 
            decider = "c2";     
    }
    else {
        if (d1 < d2) {
            if (strcmp(decider.c_str(), "c1")!=0) { // means it has not "c1"
                updates = true;
                decider = "c1";
            }
        }
        else {
            if (strcmp(decider.c_str(),"c2")!=0) { // means it has not "c2"
                updates = true;
                decider = "c2";
            }
        }
    }
    

}

/// <summary>
/// Function Name: LabelValues
/// Description : Once the true centeroids have been decided, the function labels the higher clusters image values as white
///               and lower clusters image values as black. Correspondingly the integer array is also assigned 1 and 0 based
///               on the cluster it is assigned to.
/// Usage: TASK2
/// </summary>
void LabelValues(Mat &second, Cluster& k1, Cluster&k2,int rows, int cols, int ** &arr, string ** &clusterDecider) {

    Vec3b black, white;
    black[0] = 0; black[1] = 0; black[2] = 0;
    white[0] = 255; white[1] = 255; white[2] = 255;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (k1 > k2) {
                if (strcmp(clusterDecider[r][c].c_str(), "c2") == 0) {
                    second.at<Vec3b>(r, c) = white;
                    arr[r][c] = 1;
                }
                else {
                    second.at<Vec3b>(r, c) = black;
                    arr[r][c] = 0;
                }
            }
            else {
                if (strcmp(clusterDecider[r][c].c_str(), "c1") == 0) {
                    second.at<Vec3b>(r, c) = white;
                    arr[r][c] = 1;
                }
                else {
                    second.at<Vec3b>(r, c) = black;
                    arr[r][c] = 0;
                }
            }

        }
    }

}


/// <summary>
/// Function Name: PathConvertor
/// Description : Changes the string path of the ground truth image to that of segmented image or original Image, depending on
///               the version called. It returns the new string value of the path.
/// Usage: TASK3
/// </summary>
string PathConvertor(string& str1, string& path, int version) {

    int index = path.find("IMD") + 3, change = 0;
    int length1 = str1.length();
    char* mychararr;
    if (version == 1) {
        mychararr = new char[str1.length() + 12];
        for (int i = 0; i < str1.length(); i++) {
            mychararr[i] = str1[i];
        }
        change = 1;
        mychararr[str1.length()] = 'm';
    }
    else {
        mychararr = new char[str1.length() + 11];
        for (int i = 0; i < str1.length(); i++) {
            mychararr[i] = str1[i];
        }
    }
    mychararr[str1.length() + change] = 'I';
    mychararr[str1.length() + change+1] = 'M';
    mychararr[str1.length() + change+2] = 'D';
    mychararr[str1.length() + change+3] = path[index]; // REMEMBER TO CHANGE
    mychararr[str1.length() + change+4] = path[index + 1];
    mychararr[str1.length() + change+5] = path[index + 2];
    mychararr[str1.length() + change+6] = '.';
    mychararr[str1.length() + change+7] = 'b';
    mychararr[str1.length() + change+8] = 'm';
    mychararr[str1.length() + change+9] = 'p';
    mychararr[str1.length() + change + 10] = '\0';
    string str = mychararr;
    delete[] mychararr;
    mychararr = NULL;

    return str;
}

/// <summary>
/// Structure Name: Node
/// Description: Node for linklist creation.
/// Usage: Task4
/// </summary>
struct Nodes {
    int data;
    Nodes* next;

    Nodes() :data(-1) {
        next = NULL;
    }
};

/// <summary>
/// Class Name : LinkedList
/// Description: Implements a linked list by using nodes.
/// Usage: Task4
/// </summary>
class LinkList {
private:
    Nodes* head;
public:
    LinkList() {
        head = NULL;
    }

    void insertAtHead(int val1) {
        if (head == NULL) {
            head = new Nodes;
            head->data = val1;
        }
        else {
            Nodes* temp;
            temp = new Nodes;
            temp->data = val1;
            temp->next = head;
            head = temp;
        }
    }
    void insertAtTail(int val1) {
        Nodes* temp;
        Nodes* temp2;
        temp = head;
        if (head == NULL) {
            head = new Nodes;
            head->data = val1;
        }
        else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp2 = new Nodes;
            temp2->data = val1;
            temp->next = temp2;
        }
    }
    void display(int n=0) {
        Nodes* temp = head;
        int counter = 1;
        if (n != 0) {
            for (int i = 0; i < n; i++) {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        else {
            while (temp!= NULL) {
                if (temp->data == -1) {
                    cout << temp->data << endl;
                }
                else {
                    if (counter % 2==1) {
                        cout << temp->data << " ";
                    }
                    else {
                        cout << temp->data << "   ";
                    }
                    counter++;
                }
                temp = temp->next;
            }
        }
    }
};


/// <summary>
/// Function Name: ConnectedComponentsLabelling  <============= (TASK1)
/// Description: Does connected components labelling on the image, whose path is provided as parameter.
/// </summary>
/// <returns>It returns Labeled 2d integer array which has values 1 and 0, 1 on connected components and 0 on not connected</returns>
int** ConnectedComponentsLabelling(string &path,int version=0);

/// <summary>
/// Function Name: KMeansClustering    <============== (TASK2)
/// Description: Does Kmean Clustering on the image, whose path is provided as parameter.
/// </summary>
/// <returns> It returns Labeled 2d integer array which has values 1 and 0 on lighter and darker regions.</returns>
int** KMeansClustering(string & path,int version=0);

/// <summary>
/// Function Name: DiceCoefficent     <===============  (TASK3)
/// Description: Calculates the DiceCoefficent of the TASK1 & TASK2 algorithms by calling them, on the image whose
///              path is provided as the parameter "path".
/// </summary>
void DiceCoefficent(string path);

/// <summary>
/// Function Name: RLC              <================ (TASK4)
/// Description: Performs run length code on the segmented Image whose path is provided as parameter.
/// </summary>
void RLC(string &path);



int main()
{


    string path3 = "../ground truths/IMD017_lesion.bmp";// PATH FOR TASK3
    DiceCoefficent(path3); // INSIDE IT calls TASK 1 AND 2 and shows their output, can call those functions from main too, given
                           // their actual paths. Will wait for key press and then proceed to TASK4

    string path4 = "../Segmented Outputs/mIMD091.bmp";// PATH FOR TASK4 
    RLC(path4); //Performs Task4

    return 0;
}

int ** ConnectedComponentsLabelling(string &path, int version) {

    Mat img, second;
    img = imread(path);
    second = imread(path);

    int rows = img.rows;
    int cols = img.cols;

    int** arr;
    Vec3b** temp;
    Make2D(arr, rows, cols);
    Make2D(temp, rows, cols); // dynamically allocating array
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            temp[r][c] = img.at<Vec3b>(r, c);
            arr[r][c] = temp[r][c][0];
        }
    }
    int labelCounter = 0;
    LabelMaker(arr, rows, cols, labelCounter);
    findDuplicate(arr, rows, cols); // finds and calls remove duplicates function to remove duplicates too

    int* maxLabelCounter = new int[labelCounter];
    for (int i = 0; i < labelCounter; i++) {
        maxLabelCounter[i] = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (arr[r][c] == (i + 1)) {
                    maxLabelCounter[i]++;
                }
            }
        }
    }
    int max = 0,maxIndex=0;
    for (int i = 0; i < (labelCounter); i++) {
        if (max < maxLabelCounter[i]) {
            max = maxLabelCounter[i];
            maxIndex = i;
        }
    }
    //setting values of connected components image
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (arr[r][c] == (maxIndex + 1)) {
                temp[r][c][0] = 255; temp[r][c][1] = 255; temp[r][c][2] = 255;// white
                second.at<Vec3b>(r, c) = temp[r][c];
                arr[r][c] = 1;
            }
            else {
                temp[r][c][0] = 0; temp[r][c][1] = 0, temp[r][c][2] = 0;// black
                second.at<Vec3b>(r, c) = temp[r][c];
                arr[r][c] = 0;
            }
        }
    }
    if (version == 0) {
        imshow("ORIGINAL IMAGE (SEGMENTED)", img);
        imshow("CONNECTED COMPONENTS LABELLING OUTPUT", second);
        waitKey(0);
        destroyAllWindows();
    }
    else {
        if(version!=3)
            imshow("CONNECTED COMPONENTS LABELLING OUTPUT", second);
    }
    // deleting dynamically allocated arrays
    Delete2D(temp, rows);
    delete[] maxLabelCounter;

    return arr;
}

int **KMeansClustering(string &path,int version) {
    Mat img, second;
    img = imread(path);
    second = imread(path);

    int rows = img.rows;
    int cols = img.cols;
    Cluster k1, k2;
    AssignRandomClusters(k1,k2,rows,cols,img);

    Vec3b** temp;
    string** clusterDecider;
    int** arr;

    Make2D(temp, rows, cols);
    Make2D(clusterDecider, rows, cols);
    Make2D(arr, rows, cols);

    bool updates;
    int counter = 0;
    do {
        counter++;
        if (counter != 1)
            ComputeNewCenteroids(k1, k2, rows, cols, clusterDecider, temp);
        updates = false;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                temp[r][c] = img.at<Vec3b>(r, c);
                DecideCluster(temp[r][c], k1, k2, clusterDecider[r][c], updates,counter);
            }
        }
    } while (updates);

    LabelValues(second,k1,k2,rows,cols,arr,clusterDecider);

    if (version != 2) { // used for Task2 only so output should be shown
        imshow("ORIGINAL IMAGE", img);
        imshow("K MEANS IMAGE", second);
        waitKey(0);
        destroyAllWindows();
    }
    else{
        imshow("K MEANS OUTPUT", second);
    }
    
    Delete2D(temp, rows);
    Delete2D(clusterDecider, rows);

    return arr;
}

void DiceCoefficent(string path) {
    Mat img;
    img = imread(path);

    int rows = img.rows;
    int cols = img.cols;

    double DiceCo1=0, DiceCo2=0;

    string str1="../Segmented Outputs/", str2="../Original Images/";

    string path1= PathConvertor(str1, path, 1);
    string path2=PathConvertor(str2, path, 2);

    int** arr1 = ConnectedComponentsLabelling(path1,2);
    int** arr2 = KMeansClustering(path2, 2);

    Vec3b temp;
    int TPosCounter1 = 0, FPosCounter1=0, TPosCounter2=0,FPosCounter2=0, FNegCounter1=0,FNegCounter2=0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            temp = img.at<Vec3b>(r, c);
            if (temp[0] == 255) { // only need to check one channel because ground truth images are black and white  (0,0,0) or (255,255,255)
                if (arr1[r][c] == 1)
                    TPosCounter1++;
                else
                    FNegCounter1++;
                if (arr2[r][c] == 1)
                    TPosCounter2++;
                else
                    FNegCounter2++;
            }
            else {
                if (arr1[r][c] == 1) 
                    FPosCounter1++;             
                if (arr2[r][c] == 1) 
                    FPosCounter2++;           
            }
        }
    }
    DiceCo1 = (2 * TPosCounter1) / double(FNegCounter1 + (2 * TPosCounter1) + FPosCounter1);
    DiceCo2 = (2 * TPosCounter2) / double(FNegCounter2 + (2 * TPosCounter2) + FPosCounter2);
    cout << endl;
    cout << endl;
    cout << "***************************************************************" <<endl;
    cout << "*                                                             *"<< endl;
    cout << "* Dice Coefficent: Connected Components Label    =  " << DiceCo1 << "  *" <<endl;
    cout << "* Dice Coefficent: K-MEAN Clustering             =  " << DiceCo2 << "  *" << endl;
    cout << "*                                                             *" << endl;
    cout << "***************************************************************" << endl;
    cout << endl;
    cout << endl;

    imshow("GROUND TRUTH OUTPUT", img);
    waitKey(0);

    Delete2D(arr1,rows);
    Delete2D(arr2, rows);


}

void RLC(string &path) {
    Mat img;
    img = imread(path);

    int rows = img.rows,cols= img.cols;

    LinkList list;
    list.insertAtHead(rows);
    list.insertAtTail(cols);

    bool found, atlesion;
    Vec3b temp;

    for (int r = 0; r < rows; r++) {
        found = false; atlesion = false;
        for (int c = 0; c < cols; c++) {
            temp = img.at<Vec3b>(r, c);
            if (temp[0] == 255) {
                if (!atlesion) {
                    list.insertAtTail(c + 1);
                    found = true;
                    atlesion = true;
                }
            }
            else {
                if (atlesion) {
                    list.insertAtTail(c);
                    atlesion = false;
                }
            }
            if (!found && (c==cols-1)) {
                list.insertAtTail(-1);
            }
            else {
                if (atlesion && (c==cols - 1)) {
                    list.insertAtTail(cols);
                    list.insertAtTail(-1);
                }
                else {
                    if (!(atlesion) && (c == cols - 1)) {
                        list.insertAtTail(-1);
                    }
                }
            }
        }
    }
    list.display();
}