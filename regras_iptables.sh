#!/bin/bash
# Script de provisionamento de regras IPTables para emulação de alta carga
echo "Injetando 1000 regras de filtragem na tabela PREROUTING..."

for i in {1..1000}; do
   iptables -A PREROUTING -t nat -p tcp --dport $((1000 + i)) -j ACCEPT
done

echo "Sucesso! 1000 regras lineares O(N) aplicadas ao subsistema Netfilter."