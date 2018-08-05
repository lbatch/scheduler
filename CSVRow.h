#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::size_t;
using std::getline;
using std::stringstream;
using std::istream;

class CSVRow
{
    private:
        vector<string> m_data;
    public:
        CSVRow(){
            
        }
        string const& operator[](size_t index) const
        {
            return m_data[index];
        }
        size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(istream &str)
        {
            string line;
            getline(str, line);
            stringstream lineStream(line);
            string cell;

            m_data.clear();

            while(getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
            if(!lineStream && cell.empty())
            {
                m_data.push_back("");
            }
        }
};