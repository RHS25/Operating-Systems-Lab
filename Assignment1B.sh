#!/bin/bash

opt=1

while [ $opt -lt 6 ]
do
    echo -e "1. Create\n2. View\n3. Insert\n4. Delete\n5. Modify\n6. Exit"
    read opt
    case $opt in
        1)
            echo "CreateRecord()"
            echo "Enter the file name:"
            read filename
            echo -e "Name\t Address\t MbNumber" >> $filename
            cont=1
            while [ $cont -gt 0 ]
            do
                echo "Enter the name:"
                read Name
                echo "Enter Address:"
                read Address
                echo "Enter MbNumber:"
                read MbNumber

                echo -e "$Name\t $Address\t $MbNumber" >> $filename

                echo "Do you want to continue? Enter 1 to continue & Enter 0 to stop:"
                read cont
            done
            ;;
        2)
            echo "ViewRecord()"
            echo "Enter the file name:"
            read filename
            cat $filename
            ;;
        3)
            echo "InsertRecord()"
            echo "Enter the file name:"
            read filename
            cont=1
            while [ $cont -gt 0 ]
            do
                echo "Enter Name:"
                read Name
                echo "Enter Address:"
                read Address
                echo "Enter MbNumber:"
                read MbNumber
                echo -e "$Name \t $Address \t $MbNumber" >> $filename

                echo -e "Do you want to continue? Enter 1 to continue & Enter 0 to stop:"
                read cont
            done
            ;;
        4)
            echo "DeleteRecord()"
            echo "Delete record - Enter name or MbNumber:"
            read pattern
            temp="temp.txt"
            grep -v "$pattern" $filename > $temp
            mv $temp $filename
            ;;
        5)
            echo "ModifyRecord()"
            echo "Enter the name or MbNumber to modify:"
            read pattern
            temp="temp.txt"
            grep -v "$pattern" $filename > $temp
            mv $temp $filename
            echo "Enter new name:"
            read name
            echo "Enter new address:"
            read address
            echo "Enter new mobile number:"
            read MbNumber
            echo -e "$name \t $address \t $MbNumber" >> $filename
            ;;
        6)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid option. Please select a valid option."
            ;;
    esac
done
