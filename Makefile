.PHONY: clean All

All:
	@echo "----------Building project:[ DrawALine - Debug ]----------"
	@cd "DrawALine" && "$(MAKE)" -f  "DrawALine.mk"
clean:
	@echo "----------Cleaning project:[ DrawALine - Debug ]----------"
	@cd "DrawALine" && "$(MAKE)" -f  "DrawALine.mk" clean
