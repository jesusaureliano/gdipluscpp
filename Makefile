.PHONY: clean All

All:
	@echo "----------Building project:[ SistemasDeCoordenadas - Debug ]----------"
	@cd "SistemasDeCoordenadas" && "$(MAKE)" -f  "SistemasDeCoordenadas.mk"
clean:
	@echo "----------Cleaning project:[ SistemasDeCoordenadas - Debug ]----------"
	@cd "SistemasDeCoordenadas" && "$(MAKE)" -f  "SistemasDeCoordenadas.mk" clean
