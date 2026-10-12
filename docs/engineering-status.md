# Build portavel e verificacao fisica

Removido build_dir absoluto do computador do autor. PlatformIO usa agora
.pio/build dentro do projeto. A plataforma espressif32 foi fixada em 7.1.3,
versao instalada no ambiente utilizado para a compilacao desta revisao.
Dependencias de bibliotecas ainda possuem faixas no platformio.ini; registrar
as versoes resolvidas no log e fixar ao homologar uma placa.

Compilacao: `pio run`. Esse comando nao grava firmware. TESTADO
AUTOMATICAMENTE deve ser registrado separadamente de TESTADO EM HARDWARE.
Flash 16 MB/PSRAM OPI sao configuracoes do projeto; modelo da placa real,
capacidade efetiva, OLED e niveis de logica precisam ser confirmados.

ALTO: confrontar placa/modulo e pinagem com datasheet; MEDIO: testar leitura
de entradas, debounce, limites e ausencia de bloqueios; BAIXO: medir consumo.
Consumo e latencia de entrada: NOT_MEASURED. Nao testar radio em terceiros.

Para entender esta implementacao: estude platformio.ini, fluxo do loop,
debounce e chamadas bloqueantes. Desafio: registre tempo maximo de resposta
do menu durante uma operacao de diagnostico em bancada autorizada.

Referencia: [PlatformIO build_dir](https://docs.platformio.org/en/latest/projectconf/sections/platformio/options/directory/build_dir.html).
Motivo: remover dependencia de caminho local e tornar o build reproduzivel.
