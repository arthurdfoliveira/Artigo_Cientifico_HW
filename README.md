# Impacto de Mecanismos de Redirecionamento eBPF e IPTables no Débito e Latência de Redes de Contentores sob Alta Carga

Este repositório contém os artefatos, códigos de simulação, dados brutos e scripts de análise estatística utilizados para a elaboração do artigo científico desenvolvido para a unidade curricular de **Infraestrutura de Hardware** na **CESAR School**.

## 👤 Autor
* **Arthur da Fonte de Oliveira** - Graduação em Ciência da Computação (CESAR School)

---

## 📄 Resumo do Artigo
A orquestração moderna de sistemas em nuvem depende intrinsecamente da eficiência do encaminhamento de pacotes na camada de rede de contentores. Este artigo analisa o impacto do processamento sequencial baseado em IPTables em comparação com a execução em espaço de núcleo via Extended Berkeley Packet Filter (eBPF). O problema central consiste em quantificar a degradação do débito e da latência à medida que tabelas de encaminhamento escalam sob cargas computacionais severas. 

Através de uma metodologia experimental rigorosa baseada em 35 repetições controladas e isolamento estrito de hardware, avaliou-se o desempenho de ambas as tecnologias. Os resultados revelam que o mecanismo eBPF sustenta um débito médio superior em 37.7% comparativamente ao IPTables, além de reduzir a latência média de 12.42 ms para 4.18 ms. A análise estatística, validada pelo Teste t de Student (p < 0.05), confirma que o eBPF anula a complexidade de procura linear, oferecendo previsibilidade e escalabilidade para microserviços saturados. Conclui-se que a transição para caminhos de dados programáveis baseados em eBPF é imperativa para infraestruturas de alto desempenho.

---

## 🛠️ Especificações do Ambiente de Testes

Para garantir o rigor metodológico e mitigar o ruído gerado pelo sistema operacional virtualizado, o ambiente foi configurado da seguinte forma:
* **Processador:** Intel Core i7-1165G7 (4 núcleos físicos, 8 threads, clock base de 2.80 GHz)
* **Memória RAM:** 16 GB DDR4
* **Ambiente de Virtualização:** WSL2 (Windows Subsystem for Linux)
* **Sistema Operacional Host:** Microsoft Windows 11 Home (Versão 23H2)
* **Distribuição Guest:** Ubuntu 22.04.3 LTS
* **Kernel:** Linux 5.15.153.1-microsoft-standard-WSL2

### Procedimentos de Controle de Variáveis:
1. **Windows 11 Power Plan:** Fixado manualmente em "Desempenho Máximo" para evitar flutuações dinâmicas de clock na CPU.
2. **Isolamento via `.wslconfig`:** Criação de arquivo de configuração estática no perfil do usuário do Windows para limitar os recursos do WSL2 e mitigar a concorrência com o host.
3. **Descarte de Warm-Up:** Execução e descarte explícito das 5 primeiras sessões de teste para aquecimento de caches e tabelas ARP.

---

## 📂 Estrutura do Repositório

* `analise.py`: Script Python estruturado para validação estatística.
* `dados_brutos.csv`: Dataset contendo as 35 rodadas gravadas.
* `filtro_ebpf.c`: Código-fonte em C do programa eBPF para o gancho TC.
* `regras_iptables.sh`: Script Bash para injeção das 1.000 regras lineares.

---

## 📊 Principais Resultados Compilados

| Mecanismo Experimental | Débito Médio (req/s) | Latência Média (ms) | Confiança (Latência) | Complexidade |
| :--- | :---: | :---: | :---: | :---: |
| **IPTables** | 45.120 | 12,42 | [12,04 ; 12,80] | $O(N)$ - Linear |
| **eBPF** | 62.150 | 4,18 | [4,08 ; 4,28] | $O(1)$ - Constante |

**Conclusão Estatística:** O Teste t de Student bicaudal independente gerou um valor de estatística $t = -23,84$ e um $p < 0,0001$, rejeitando terminantemente a hipótese nula ($H_0$) e provando a relevância matemática superior do eBPF sob alta carga.

---

## 🚀 Como Executar a Análise Estatística

Se desejar reproduzir a validação estatística dos dados, certifique-se de ter o Python 3 e a biblioteca `numpy` instalados. Execute no terminal:

```bash
# Instalar as dependências necessárias no ambiente WSL2
pip install pandas scipy numpy

# Executar o script de análise estatística
python analise.py
