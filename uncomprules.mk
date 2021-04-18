# convert binary to object file
$(BUILD_DIR)/%.szp.o: $(BUILD_DIR)/%.bin
	$(call print,Converting BIN to ELF:,$<,$@)
	$(V)printf ".section .data\n\n.incbin \"$<\"\n" | $(AS) $(ASFLAGS) -o $@