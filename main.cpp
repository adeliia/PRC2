#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class PbmImage
{
public:
    using Bit = bool;
    void load(const string &path);
    void printBits();
    void save(const string &path);

private:
    vector<vector<Bit>> pbmBits;

    using vectorColumnType = decltype (pbmBits);
    using vectorRowType = vectorColumnType::value_type;
    using PbmDimensions = pair<vectorColumnType::size_type, vectorRowType::size_type>;
    PbmDimensions pbmDimensions;

    PbmDimensions readPbmDimensions(istream &stream) const;
    bool readPbmHeader(istream &stream) const;

public:
    using ColumnDimensionType = PbmImage::vectorColumnType::size_type;
    using RowDimensionType = PbmImage::vectorRowType::size_type;
    void setBit(ColumnDimensionType i, RowDimensionType j, Bit bit);
    bool getBit(ColumnDimensionType i, RowDimensionType j);
    void seedFill4(PbmImage::RowDimensionType i, PbmImage::ColumnDimensionType j, Bit bit);
};

void PbmImage::load(const string &path)
{
    fstream pbmFile;
    pbmFile.open(path);
    if(pbmFile){
        if(readPbmHeader(pbmFile))
        {
            pbmDimensions = readPbmDimensions(pbmFile);
            for (PbmDimensions::first_type rowIndex=0; rowIndex < pbmDimensions.second; rowIndex++) {
                //new vector for each row
                pbmBits.push_back(vectorRowType());
                for(PbmDimensions::first_type columnIndex = 0; columnIndex < pbmDimensions.first; columnIndex++) {
                    Bit bit;
                    pbmFile >> bit;
                    pbmBits[rowIndex].push_back(bit);
                }
            }
            pbmFile.close();
        } else {
            //else error
        }
    } else {
        //error
    }

}

bool PbmImage::readPbmHeader(istream &mystream) const
{
    std::string header;
    mystream >> header;
    return (header == "P1");
}

PbmDimensions PbmImage::readPbmDimensions(istream &stream) const
{
    PbmDimensions dimensions;
    stream << dimensions.first << dimensions.second;
    return dimensions;
}

void PbmImage::printBits()
{
    for(pbmDimensions::first_type rowIndex=0; rowIndex < pbmDimensions.second; rowIndex++)
    {
        for(pbmDimensions::first_type columnIndex = 0; columnIndex < pbmDimensions.first; columnIndex++)
        {
            cout << pbmBits[rowIndex][columnIndex] << " ";
        }
        cout << endl;
    }
}

void PbmImage::save(const string &path)
{
    fstream pbmFile;
    pbmFile.open(path, std::fstream::out);
    if(pbmFile)
    {
        pbmFile << "P1" << endl;
        pbmFile << pbmDimensions.first << " " << pbmDimensions.second << endl;
        for(pbmDimensions::first_type rowIndex=0; rowIndex < pbmDimensions.second; rowIndex++)
        {
            for(pbmDimensions::first_type columnIndex = 0; columnIndex < pbmDimensions.first; columnIndex++)
            {
               pbmFile << pbmBits[rowIndex][columnIndex] << " ";
            }
            pbmFile << endl;
        }
        pbmFile.close();
    } else {
        //error
    }
}

void PbmImage::setBit(ColumnDimensionType i, RowDimensionType j, Bit bit)
{
    //perform check of dimensions -> getFIrstDimension, getSecondDimension
    pbmBits[i][j] = bit;
}

PbmImage::Bit PbmImage::getBit(ColumnDimensionType i, RowDimensionType j)
{
    return pbmBits[i]][j];
}

void PbmImage::seedFill4(PbmImage::RowDimensionType i, PbmImage::ColumnDimensionType j, Bit bit)
{
    if(i < 0 || j < 0 || i >= pbmDimensions.second || j >= pbmDimensions.first) return;
    Bit bitTobeChanged = pbmBits[i][j];
    if(bitTobeChanged == bit ) return;
    pbmBits[i][j] = bit;
    SeedFill4(i+1, j, bit);
    SeedFill4(i-1, j, bit);
    SeedFill4(i, j+1, bit);
    SeedFill4(i, j-1, bit);
}

int main()
{
    PbmImage image;
    image.load("//fjfi.cvut.cz/ark/Home/gatauade/PRC2/cv1_1/MARBLES.PBM");
    image.printBits();

    image.save("//fjfi.cvut.cz/ark/Home/gatauade/PRC2/cv1_1/MARBLES_duplicate.PBM");
    image.seedFill4(1, 1, 0);
    image.printBits();
    image.save("//fjfi.cvut.cz/ark/Home/gatauade/PRC2/cv1_1/MARBLES_afterSeedFill.PBM");

    return 0;
}
