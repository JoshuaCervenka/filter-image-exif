#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    ifstream in("snap_ReceiveJpeg/tmpJpegFile.jpg", ios::in | ios::binary);

    istream_iterator<unsigned char> begin(in), end;
    vector<unsigned int> stripped_buffer(begin, end);

    /*for (int i=0; i<stripped_buffer.size(); i++)
    {
        cout << stripped_buffer[i];
    }*/
    ifstream orig_in("snap_ReceiveJpeg/tmpJpegFile.jpg_original", ios::in | ios::binary);

    istream_iterator<unsigned char> start(orig_in), finish;
    vector<unsigned int> original_buffer(start, finish);
    
    int orig_size = original_buffer.size();
    int strip_size = stripped_buffer.size();

    if (strip_size < orig_size)
    {
        cout << "Original Image Size: " << orig_size << endl;
        cout << "Stripped Image Size: " << strip_size << endl;
        cout << "Validated that EXIF data was stripped" << endl;
    }
    else if (stripped_buffer.size() == original_buffer.size())
    {
        cout << "EXIF data was not stripped" << endl;
    }
}
