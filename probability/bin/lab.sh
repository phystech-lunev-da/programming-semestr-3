#! /bin/fish
./probability
cp bonusdice_data.csv ../data/bonusdice_data.csv
cp penaltydice_data.csv ../data/penaltydice_data.csv
cp threedicepool_data.csv ../data/threedicepool_data.csv
cd ../data
python3 ../data/data_processing.py
cd ../bin