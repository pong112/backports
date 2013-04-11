#ifndef __BACKPORT_LIST_H
#define __BACKPORT_LIST_H
#include_next <linux/list.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
/**
 * backport:
 *
 * commit 0bbacca7c3911451cea923b0ad6389d58e3d9ce9
 * Author: Sasha Levin <sasha.levin@oracle.com>
 * Date:   Thu Feb 7 12:32:18 2013 +1100
 *
 *     hlist: drop the node parameter from iterators
 */
#include <backport/magic.h>

#undef hlist_entry_safe
#define hlist_entry_safe(ptr, type, member) \
	(ptr) ? hlist_entry(ptr, type, member) : NULL

#define hlist_for_each_entry4(tpos, pos, head, member)			\
	for (pos = (head)->first;					\
	     pos &&							\
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;});\
	     pos = pos->next)

#define hlist_for_each_entry_safe5(tpos, pos, n, head, member)		\
	for (pos = (head)->first;					\
	     pos && ({ n = pos->next; 1; }) &&				\
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;});\
	     pos = n)

#define hlist_for_each_entry3(pos, head, member)				\
	for (pos = hlist_entry_safe((head)->first, typeof(*(pos)), member);	\
	     pos;								\
	     pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

#define hlist_for_each_entry_safe4(pos, n, head, member) 			\
	for (pos = hlist_entry_safe((head)->first, typeof(*pos), member);	\
	     pos && ({ n = pos->member.next; 1; });				\
	     pos = hlist_entry_safe(n, typeof(*pos), member))

#undef hlist_for_each_entry
#define hlist_for_each_entry(...) \
	macro_dispatcher(hlist_for_each_entry, __VA_ARGS__)(__VA_ARGS__)
#undef hlist_for_each_entry_safe
#define hlist_for_each_entry_safe(...) \
	macro_dispatcher(hlist_for_each_entry_safe, __VA_ARGS__)(__VA_ARGS__)

#endif

#endif /* __BACKPORT_LIST_H */
