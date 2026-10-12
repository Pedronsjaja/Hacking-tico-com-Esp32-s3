# Instrucoes do projeto

Firmware Arduino ESP32-S3, OLED e entrada em src/; platformio.ini define o alvo. Usar apenas funcoes de diagnostico autorizadas. Nao inferir pinagem/tensao de um modulo apenas pelo nome ESP32-S3.

Ler README e docs antes de alterar. Preservar arquitetura, dados brutos e
autoria/licencas dos materiais externos. Nao inventar hardware, medidas ou
resultados. Marcar UNKNOWN/NOT_MEASURED e separar SIMULATED de REAL.
Fazer mudancas pequenas, com regressao para defeitos corrigidos.

Validacao: `pio run` compila; nao usar upload/flash para validar software sem placa e pinagem confirmadas.

Definition of Done: verificacoes pertinentes, documentacao das alteracoes,
comandos reproduziveis e limites de validacao. Inspecao estatica nao comprova
funcionamento fisico. Ver docs/engineering-status.md para prioridades e estudo.
