#include "string.h"
#include "kmp.h"

char *txt1 = "\
        A Grain Of Sand\n\
            (William Black)\n\
    To see a world in a grain of sand\n\
    And a heaven in a wild flower,\n\
    Hold infinity in the palm of your hand\n\
    And eternity in an hour.\n\
";

char *txt2 = "\
    译文：\n\
        一粒沙子\n\
            （威廉·布莱克）\n\
    从一粒沙子看到一个世界，\n\
    从一朵野花看到一个天堂，\n\
    把握在你手里的就是无限，\n\
    永恒也就包含在一小时中。\n\
";

int main(int argc, char const *argv[])
{
    string str;
    string p1;
    string p2;

    string_init(&str);
    string_init(&p1);
    string_init(&p2);
    string_assign(&str, txt1);
    string_assign(&str, txt2);
    string_echo(&str);

    // 匹配模式串
    string_assign(&p1, " in ");
    string_echo(&p1);
    // kmp_index(&str, &p1, 1);
    int i = 0;
    do {
        i = kmp_index(&str, &p1, i+1);
        if (i != 0) printf("index = %d\n", i);
    } while (i != 0);
    
    // 匹配模式串
    string_assign(&p2, "一个世界");
    string_echo(&p2);
    i = kmp_index(&str, &p2, 1);
    printf("index = %d\n", i);

    string_destroy(&str);
    string_destroy(&p1);
    string_destroy(&p2);

    return 0;
}
