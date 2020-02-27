#ifndef _LOOKUP_H_
#define _LOOKUP_H_

#include <stdbool.h>
#include "kpatch-elf.h"

#define KSYM_NAME_LEN 128

struct lookup_table;

struct lookup_result {
	char *objname;
	unsigned long addr;
	unsigned long size;
	unsigned long sympos;
	bool global, exported;
};

struct lookup_refsym {
	char *name;
	unsigned long addr;
};

struct lookup_table *lookup_open(char *symtab_path, char *objname,
				 char *symvers_path, struct kpatch_elf *kelf);
void lookup_close(struct lookup_table *table);
bool lookup_symbol(struct lookup_table *table, struct symbol *sym,
		   struct lookup_result *result);
int lookup_is_duplicate_symbol(struct lookup_table *table, char *name,
		char *objname, unsigned long pos);
int lookup_ref_symbol_offset(struct lookup_table *table,
		struct symbol *lookup_sym,
		struct lookup_refsym *refsym, char *objname,
			 long *offset);
unsigned long get_vmlinux_duplicate_symbol_pos(struct lookup_table *table, char *name,
                         unsigned long addr);

#endif /* _LOOKUP_H_ */
