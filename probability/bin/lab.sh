#! /bin/fish

if test -f bonusdice_data.csv
    rm bonusdice_data.csv
end

if test -f penaltydice_data.csv
    rm penaltydice_data.csv 
end

if test -f threedicepool_data.csv
    rm threedicepool_data.csv 
end

if test -f doubledice_data.csv
    rm doubledice_data.csv 
end

if test -f doubledice_data_with_inheritance.csv
    rm doubledice_data_with_inheritance.csv 
end

./probability
cp -f bonusdice_data.csv ../data/bonusdice_data.csv
cp -f penaltydice_data.csv ../data/penaltydice_data.csv
cp -f threedicepool_data.csv ../data/threedicepool_data.csv
cp -f doubledice_data.csv ../data/doubledice_data.csv
cp -f doubledice_data_with_inheritance.csv ../data/doubledice_data_with_inheritance.csv
cd ../data
python3 ../data/data_processing.py
cd ../bin