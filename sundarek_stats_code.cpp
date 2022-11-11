//Kavya Sundaresan
//400307169
//sundarek

#include <iostream>
#include <math.h>
#include <string>
using namespace std;

// Define classes here 
class Stats {
    public:
        int *array1;
        int count;
        Stats (int *a, int l);
        Stats(Stats& a) { //copy constructor
            count = a.count; //assigns size of array to member variable
            array1 = new int[count];
            for (int i=0; i<count; i++) { //copies array to member array
                array1[i] = a.array1[i];
            }  
            for (int i=0; i<count; i++) { //searches for max value in array and assigns it to member variable
                if (array1[i+1]>array1[i]) {
                    maxval = array1[i+1];
                }
            }
        }
        virtual void computeStats() {
            float total = 0;
            for (int i=0; i<count; i++) { //sums up all values in array
                total += array1[i];
            }
            mean = total/count; //calculates mean

            double var = 0.0;
            for (int i=0; i<count; i++){ //stdev calculationn
                var += pow(array1[i] - mean, 2);
            }
            var = var / count; // variance
            stdev = sqrt(var); // standard deviation
        }
        virtual void printStats() {
            cout << "mean= " << mean << '\t' << "stdev= " << stdev << endl; //outputs mean and stdev
        }
        float getMean();
        float getStdev();
        virtual ~Stats();
    protected:
        float maxval;
    private:
        float mean;
        float stdev;
};

Stats::Stats (int *a, int l) { //receives pointer to array and array size
    count = l; //stores array size in member variable
    array1 = new int[count];
    for (int i=0; i<count; i++) { //copies array to member variable
        array1[i] = a[i];
    }  

    for (int i=0; i<count; i++) { //searches for maximum value in array and stores it in member variable
        if (array1[i+1]>array1[i]) {
            maxval = array1[i+1];
        }
    }    
}

float Stats::getMean() { //gets and returns mean
    return mean;
}

float Stats::getStdev() { //gets and returns stdev
    return stdev;
}

Stats::~Stats() {
    delete [] array1;
}


class OneVarStats : virtual public Stats {
    public:
        OneVarStats (int *a, int l) : Stats(a, l) {
            histLength = maxval+1;  //calculate size of hist array
            hist = new int[histLength]; //makes hist array
            for (int i=0; i<histLength; i++) { //sets all values in hist array to 0
                hist[i] = 0;
            }  
        }
        virtual void computeStats() {
            Stats::computeStats();
            int freq = 0;
            for (int i=0; i<histLength; i++) { //computes frequency of each number in the array
                for (int j=0; j<count; j++) {
                    if (array1[j] ==i) {
                        freq++;
                    }
                }
                hist[i] = freq; //adds frequency to hist array
                freq = 0;
            }
        }
        virtual void printStats() {
            Stats::printStats();
            for (int i=0; i<histLength; i++) { //prints hist array
                cout << hist[i] << '\t';
            }
            cout << '\n';
        }
        ~OneVarStats();
    private:
        int histLength;
        int *hist;
};


OneVarStats::~OneVarStats() {
    delete [] hist;
}



class TwoVarStats : virtual public Stats {
    public:
        TwoVarStats(int *a1, int *a2, int length);
        double computeCorrCoef();
        ~TwoVarStats();
        virtual void computeStats() {
            Stats::computeStats();
            correlationCoef = computeCorrCoef();
        }
        virtual void printStats() {
            Stats::printStats(); //outputs correlation coef
            cout << "corr coeff= " << correlationCoef <<endl;
        }

    private:
        int *array2;
        double correlationCoef;

};

TwoVarStats::TwoVarStats(int *a1, int *a2, int length) : Stats(a1, length) {
    array2 = new int[length];
    for (int i=0; i<length; i++) { //copies a2 to member variable
        array2[i] = a2[i];
    }
    correlationCoef = 0;
}

TwoVarStats::~TwoVarStats() {
    delete [] array2;
}

// the correlation coefficient function 
double TwoVarStats::computeCorrCoef() {  // works on array1 and array2 and count
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0;  // hold S(x), S(y), S(xy) respectively.
    double sumX2 = 0.0, sumY2 = 0.0;  // hold S(x^2), S(y^2) respectively.
    
    for (int i=0; i< count; i++){
        sumX += array1[i];
        sumY += array2[i];
        sumXY += array1[i] * array2[i];

        sumX2 += array1[i] *  array1[i];
        sumY2 += array2[i] *  array2[i];
    } 
    double corr_coef = (count * sumXY - sumX * sumY)/ (sqrt((count * sumX2 - sumX * sumX) * (count * sumY2 -  sumY * sumY))); 
    correlationCoef = corr_coef;
    return correlationCoef;
}


int main( ) {
    int x[] = {2, 4, 7, 11, 5};
    int y[] = {5, 9, 14, 20, 10};
    int z[] = {14, 7, 4, 9, 21};

    int stats_len = 4;
    Stats* pp[stats_len];
    pp[0] = new Stats(x, 5);
    pp[1] = new OneVarStats (x,  5);
    pp[2] = new TwoVarStats (x, y, 5);
    pp[3] = new TwoVarStats (y, z, 5);

    for (int i=0; i < stats_len; i++){
        pp[i]->computeStats();
        cout << "\n";
    }

    for (int i=0; i < stats_len; i++){
        pp[i]->printStats();
        cout << "\n";
    }
}