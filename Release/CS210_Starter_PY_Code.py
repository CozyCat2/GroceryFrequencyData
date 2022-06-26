import re
import string

itemsFile = open("CS210_Project_Three_Input_File.txt", 'r')
itemsCount = {}

for line in itemsFile:
    #remove new line character from name
    trimmedLine = line[:-1]
    if trimmedLine in itemsCount.keys():
        #increment if item is already added to list
        itemsCount[trimmedLine] = itemsCount[trimmedLine] + 1
    else:
        #set item to 1 if not already in list
        itemsCount[trimmedLine] = 1;

#close file now that we're done
itemsFile.close()


def PrintSomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

#shows list of all items purchased
#and their respective purchase count
def DisplayAllItemCount():
    for key in itemsCount:
        print(key, itemsCount[key])

    #print extra line for display purposes
    print()

#displays just the purchase count of a
#specific item
def DisplayItemCount(itemName):
    #if requested item exists
    if(itemName in itemsCount.keys()):
        #return item count from file
        return itemsCount[itemName]
    else: #item doesn't exist in list
        #return -1 to signify item not found
        return -1


#displays a text-based histogram of 
#item purchase popularity
def WriteOutFrequency():

    #open file frequency.dat
    frequencyFile = open("frequency.dat", 'w')
    #for each grocery item we stored
    for index, item in enumerate(itemsCount):
        #write item to the file
        frequencyFile.write(item)
        #then a space
        frequencyFile.write(' ')
        #then write the number of times it's purchased
        frequencyFile.write(str(itemsCount[item]))
        #then if it's not the last item, print a new line char
        if not (index == len(itemsCount) - 1):
            frequencyFile.write('\n')
    #close frequency file
    frequencyFile.close()
