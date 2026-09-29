#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string>
#include <stdexcept>
using namespace std;

void testIoTDataSample(){ 
    string fileLocation = "iot-shard.txt";
    ifstream file(fileLocation);

    if(!file){ string error_msg = fileLocation + " was not open properly!";
         throw std::runtime_error(error_msg); 
        }
        
    string line;
    //get the first line that contains all the attribute' titles 
    getline(file, line);
    //make a stringstream of the line to further tokenize each attribute 
    stringstream lineString(line); 
    int size(0); 
    string token;
    string attributes = "Attributes: [";
    //extract each token seperated by ',' 
    while (getline(lineString, token, ',')) { 
        cout<<token<<endl;
        attributes += token + ", "; 
        // count the number of attributes 
        ++size; 
    } 

    attributes += "]";

    cout << "\nTotally #" << size << " attributes!\n" <<endl;
     //processing each line and store each line's value into one RankOneTensor object.
     // when end_of_file is encountered, the while condition is false;

    int tokenCount= 0;
    while(getline(file, line)){
        string outfilename = "shard_" + to_string(tokenCount++) + ".txt";
        ofstream inFileStream(outfilename);
        if(!inFileStream){ string error_msg = fileLocation + " was not open properly!";
         throw std::runtime_error(error_msg); //check if the file is opened properly
        }
        lineString.clear(); // clears the eof and fail flags
        lineString.str("");  // clear the content of the stringstream
        lineString.str(line); // set the content to the new line
        string token; 
        //Print out the data line by line using stringstream. 
        cout << "Data : [";
        stringstream toFile; 
        toFile << attributes << endl;
        toFile << "Data : [";
        // stopping condition is that stringstream reaches to the end of the line;
        //eofbit is set for ss;
        while (lineString >> token) { 
            cout << token << "," ; 
            toFile << token << ",";
        } 
        toFile << "]" << endl;
        cout << "]" << endl; 
        inFileStream << toFile.str();
        inFileStream.close();
    }
    file.close(); 
}


void IOTsampleProcessing(string& nattributes, string& nshard){ //default 1 sample per shard deserialization
    ifstream file("iot-shard.txt");
    if(!file){ string error_msg = "iot-shard.txt was not open properly!";
         throw std::runtime_error(error_msg); 
        }
    
    int attributeSize = 0;
    string line;
    string attribute;

    stringstream attributesStream;
    stringstream sampleStream;

    getline(file, line);
    stringstream attributeline(line);
    
    while (getline(attributeline, attribute, ',')) { 
        attributesStream<<attribute<<endl;
        attributeSize++; 
    }

    attributesStream << endl << "There are " << attributeSize << " attributes!" << endl << endl;

    while(getline(file, line, '\n')){
        sampleStream << "Data : [" << line << "]" << endl;

    }
    file.close();
    
    
    nattributes = attributesStream.str();
    nshard = sampleStream.str();

}

void IOTsampleToFile(int shardSize = 1){
    string attributes, completeshard, shard;
    int numLines=0, numShards, shardsRemaining;
    IOTsampleProcessing(attributes, completeshard);
    
    stringstream shardStream(completeshard);
    while(getline(shardStream, shard, '\n')){
        numLines++;
    }
    shardsRemaining = numLines;
    if (numLines % shardSize != 0){
        numShards = (numLines / shardSize) + 1;
    }
    else{
        numShards = numLines / shardSize;
    }

    shardStream.clear();
    shardStream.str("");
    shardStream.str(completeshard);

    for (int i = 0; i < numShards; i++){
        string outfilename = "iot_shard_" + to_string(i) + ".txt";
        ofstream outFileStream(outfilename);
        
        if(!outFileStream){ string error_msg = outfilename + " was not open properly!";
         throw std::runtime_error(error_msg); 
        }
        outFileStream << attributes << endl;
        for(int j = 0; j < shardSize; j++){
            getline(shardStream, shard, '\n');
            outFileStream << shard << endl;
            shardsRemaining--;
            if (shardsRemaining == 0){
                break;
            }
        }
        outFileStream.close();
    }

}

int main(){ 
    //testIoTDataSample(); 
    string attributes, samples;
    int shardSize;
    cout << "Enter the desired shard size (How many lines of data you want per shard): ";
    cin >> shardSize;
    cout << endl;
    IOTsampleProcessing(attributes, samples);
    cout << attributes << samples;
    IOTsampleToFile(shardSize);
    
    system("pause");
    return 0;
}