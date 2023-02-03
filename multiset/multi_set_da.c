#include "multi_set_da.h"

struct node_s
{
    elem_t elem;
    unsigned int count;
};

struct multi_set_s
{
    node_t *nodes;
    size_t node_count, act_size, max_size;
};

static int search_node(const multi_set mset, const elem_t e)
{
    int mid, inf = 0, sup = mset->node_count;
    while (inf < sup)
    {
        mid = inf + (sup - inf) / 2;
        if (mset->nodes[mid]->elem < e)
            inf = mid + 1;
        else
            sup = mid;
    }

    if ((size_t)inf < mset->node_count && mset->nodes[inf]->elem == e)
        return inf;

    return ACTION_FAILURE;
}

static void shift_right(multi_set mset, const pos_t pos)
{
    if (mset->node_count == mset->max_size)
    {
        mset->max_size *= 2;
        mset->nodes = (node_t *)realloc(mset->nodes, mset->max_size * sizeof(node_t));
    }

    for (pos_t i = mset->node_count; i > pos; i--)
        mset->nodes[i] = mset->nodes[i - 1];
}

static node_t create_node(const elem_t e)
{
    node_t node = (node_t)malloc(sizeof(struct node_s));
    if (node)
    {
        node->elem = e;
        node->count = 1;
    }
    return node;
}

multi_set init(void)
{
    multi_set mset = (multi_set)malloc(sizeof(struct multi_set_s));
    if (mset)
    {
        mset->nodes = (node_t *)malloc(0 * sizeof(node_t));
        if (mset->nodes)
        {
            mset->node_count = 0;
            mset->act_size = 0;
            mset->max_size = 1;
        }
    }
    return mset;
}

action_status add(multi_set mset, const elem_t e)
{
    if (!mset)
        return ENULL;
    node_t new;

    pos_t i = 0;
    while (i < mset->node_count && mset->nodes[i]->elem < e)
        i++;

    if (i == mset->node_count || mset->nodes[i]->elem > e)
    {
        new = create_node(e);
        if (!new)
            return ENULL;
        shift_right(mset, i);
        mset->nodes[i] = new;
        mset->node_count++;
    }
    else
    {
        mset->nodes[i]->count++;
    }
    mset->act_size++;

    return ACTION_SUCCESS;
}

action_status rm(multi_set mset, const elem_t e)
{
    if (!mset)
        return ENULL;

    int pos = search_node(mset, e);
    if (pos >= 0)
    {
        if (mset->nodes[pos]->count > 0)
        {
            mset->nodes[pos]->count--;
            mset->act_size--;
            return ACTION_SUCCESS;
        }
    }

    return ACTION_FAILURE;
}

inline size_t act_size(const multi_set mset)
{
    if (!mset)
        return ENULL;
    return mset->act_size;
}

inline size_t max_size(const multi_set mset)
{
    if (!mset)
        return ENULL;
    return mset->max_size;
}

inline bool is_empty(const multi_set mset)
{
    if (!mset)
        return ENULL;
    return !mset->act_size;
}

action_status contains(const multi_set mset, const elem_t e)
{
    if (!mset)
        return ENULL;

    int pos = search_node(mset, e);
    if (pos >= 0)
        if (mset->nodes[pos]->count > 0)
            return ACTION_SUCCESS;

    return ACTION_FAILURE;
}

elem_t first(const multi_set mset)
{
    if (!mset)
        return ENULL;
    if (is_empty(mset))
        return ACTION_FAILURE;

    pos_t pos = 0;
    while (pos < mset->node_count && !mset->nodes[pos]->count)
        pos++;

    return mset->nodes[pos]->elem;
}

elem_t last(const multi_set mset)
{
    if (!mset)
        return ENULL;
    if (is_empty(mset))
        return ACTION_FAILURE;

    pos_t pos = mset->node_count - 1;
    while (pos > 0 && !mset->nodes[pos]->count)
        pos--;

    return mset->nodes[pos]->elem;
}

size_t count(const multi_set mset, const elem_t e)
{
    if (!mset)
        return ENULL;

    int pos = search_node(mset, e);
    if (pos >= 0)
        return mset->nodes[pos]->count;

    return ACTION_FAILURE;
}

action_status mts(multi_set mset)
{
    if (!mset)
        return ENULL;
    if (is_empty(mset))
        return ACTION_FAILURE;

    for (unsigned int i = 0; i < mset->node_count; i++)
    {
        if (mset->nodes[i]->count > 0)
        {
            mset->act_size -= mset->nodes[i]->count;
            mset->act_size++;
            mset->nodes[i]->count = 1;
        }
    }

    return ACTION_SUCCESS;
}

action_status empty(multi_set mset)
{
    if (!mset)
        return ENULL;
    if (is_empty(mset))
        return ACTION_FAILURE;

    for (unsigned int i = 0; i < mset->node_count; i++)
        mset->nodes[i]->count = 0;
    mset->act_size = 0;

    return ACTION_SUCCESS;
}

action_status dump(const multi_set mset)
{
    if (!mset)
        return ENULL;

    printf("{");
    for (unsigned int i = 0; i < mset->node_count; i++)
        for (unsigned int j = 0; j < mset->nodes[i]->count; j++)
            printf("%d ", mset->nodes[i]->elem);
    printf("}\n");

    return ACTION_SUCCESS;
}

action_status destroy(multi_set mset)
{
    if (!mset)
        return ENULL;

    for (unsigned int i = 0; i < mset->node_count; i++)
    {
        free(mset->nodes[i]);
        mset->nodes[i] = NULL;
    }

    free(mset->nodes);
    mset->nodes = NULL;
    free(mset);
    mset = NULL;

    return ACTION_SUCCESS;
}