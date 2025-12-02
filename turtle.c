#include <stdio.h>

/* What the turtle can do */
enum command {
    ROTATE_CLOCKWISE,
    MOVE_FORWARD,
    PRINT_STATE,
    NOOP,
};

enum orientation {
    NORTH, EAST, SOUTH, WEST
};


/* Where the turtle is, and which way it is facing */
struct turtle {
    int x, y;
    enum orientation orientation;
};
/*enum 是 enumeration（枚举） 的缩写，
意思是“列举出一组有限的命名常量”。*/

/* ---- 小工具函数：方向字符串、旋转、前进一步 ---- */

static const char* orientation_str(enum orientation o) {
    switch (o) {
        case NORTH: return "NORTH";
        case EAST:  return "EAST";
        case SOUTH: return "SOUTH";
        case WEST:  return "WEST";
        default:    return "?";
    }
}

/*switch 是 C 语言里的多分支条件语句，
相当于一连串的 if ... else if ... else。
enum 枚举的每个值其实就是整数：
if (o == 0) return "NORTH";
else if (o == 1) return "EAST";
else if (o == 2) return "SOUTH";
else if (o == 3) return "WEST";
else return "?";*/

/*static
只在当前源文件中可用（内部函数）*/

/* 顺时针旋转 90° */
static void rotate_clockwise(struct turtle *t) {
    if (!t) return;
    switch (t->orientation) {
        case NORTH: t->orientation = EAST;  break;
        case EAST:  t->orientation = SOUTH; break;
        case SOUTH: t->orientation = WEST;  break;
        case WEST:  t->orientation = NORTH; break;
        default: /* 不应到达 */ break;
    }
}
/*void：函数没有返回值（它只是修改乌龟状态）*/

/* 按当前朝向前进一步（步长 1） */
static void move_forward(struct turtle *t) {
    if (!t) return;
    switch (t->orientation) {
        case NORTH: t->y += 1; break;
        case SOUTH: t->y -= 1; break;
        case EAST:  t->x += 1; break;
        case WEST:  t->x -= 1; break;
        default: /* 不应到达 */ break;
    }
}
/*
*t 表示“这个指针指向一只乌龟”的内存位置。
t->x   // 等价于 (*t).x
t->y   // 等价于 (*t).y
*/
/*!t 等价于 t == NULL。防止出现“空指针访问”的错误。*/



/* ---- 你要补的两个函数：执行单条命令 & 执行程序 ---- */

/* 根据命令直接“原地修改”传入的 turtle（指针语义） */
void run_command(enum command command, struct turtle *turtle) {
    if (!turtle) return;

    switch (command) {
        case ROTATE_CLOCKWISE:
            rotate_clockwise(turtle);
            break;
        case MOVE_FORWARD:
            move_forward(turtle);
            break;
        case PRINT_STATE:
            printf("Turtle at (%d, %d), facing %s\n",
                   turtle->x, turtle->y, orientation_str(turtle->orientation));
            break;
        case NOOP:
            /* 不做任何事 */
            break;
        default:
            /* 未知命令：这里选择静默忽略，也可以报警告 */
            /* fprintf(stderr, "Warning: unknown command %d\n", command); */
            break;
    }
}

/* 顺序执行命令数组 program[0..n-1]，每条命令都作用于 *turtle */
void run_program(int n, enum command program[n], struct turtle *turtle) {
    if (!turtle || !program || n <= 0) return;

    for (int i = 0; i < n; ++i) {
        run_command(program[i], turtle);
    }
}

int main(int argc, char *argv[]) {
    struct turtle turtle = {0, 0, NORTH};
    enum command program[] = {
        MOVE_FORWARD, ROTATE_CLOCKWISE, MOVE_FORWARD, PRINT_STATE
    };

    run_program(4, program, &turtle);

    /* 可选：也可以在这里打印最终状态以验证 */
    /* run_command(PRINT_STATE, &turtle); */

    return 0;
}