void shiftleft(metadata *prev, metadata *curr)
{
    if (prev == NULL)
    {
        char temp[4096];
        int length = curr->spaceUsed;
        memcpy(temp, curr->nextNode, 4096 - length);
        memcpy(myblock, temp, 4096);
        metadata * cursor = (void *)myblock;
        char * convert = (void *)myblock;
        int swapLength = cursor->spaceUsed;
        while(cursor != NULL && cursor->nextNode != NULL)
        {
            convert += swapLength + sizeof(metadata);
            cursor->nextNode = (void *)convert;
            cursor = cursor->nextNode;
            swapLength = cursor->spaceUsed;
        }

        cursor->spaceUsed += length;
    } else {
        
    }
}

void compress()
{
    metadata *head = (void *)myblock; // Points to the first node in myblock[]
    metadata *current = head;         // Sets the current node to the cursor
    metadata *previous = NULL;
    while ((current != NULL) && (current->nextNode != NULL))
    {
        // If the current node and next node are not in use
        if ((current->inUse == 0) && (current->nextNode->inUse == 1))
        {
            shiftleft(previous, current);
        }
        previous = current;
        current = current->nextNode; // Traverse to next node
    }
}