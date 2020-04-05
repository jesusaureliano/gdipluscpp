.PHONY: clean All

All:
	@echo "----------Building project:[ DrawText - Debug ]----------"
	@cd "DrawText" && "$(MAKE)" -f  "DrawText.mk"
clean:
	@echo "----------Cleaning project:[ DrawText - Debug ]----------"
	@cd "DrawText" && "$(MAKE)" -f  "DrawText.mk" clean
