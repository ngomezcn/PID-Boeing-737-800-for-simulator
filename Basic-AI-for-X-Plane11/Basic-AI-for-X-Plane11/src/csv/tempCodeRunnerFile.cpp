            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);
            output[count][colIdx] = val;
            std::cout << colIdx;
