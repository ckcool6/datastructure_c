const int MAXSIZE = 20;
typedef int KeyType;
typedef void *InfoType;

typedef struct RecordType
{
    KeyType key;
    InfoType otherinfo;
} RecordType;

typedef struct SqList
{
    RecordType r[MAXSIZE + 1];
    int length;
} SqList;

