# case_backend
Desafio de case focado em backend para a Loja Integrada

# Instalação: passo a passo
Passo a passo para clonar o repositório e utilizar o docker compose para subir a aplicação.

## Pré-requisitos:
- Git
- Docker Desktop
- Portas que devem estar livres para que o ambiente rode com êxito:
  - 5432 - Porta utilizada pela base de dados PostgreSQL
  - 80 - Porta utilizada pelo PHP/Apache
  - 443 - Porta utilizada pelo PHP/Apache
  - 3080 - Porta utilizada pelos serviços NodeJS
  - 3000 - Porta utilizada pelo framework NextJS
## Subindo a aplicação
- Clonar o repositório em uma pasta qualquer
- Acessar a pasta raíz e abrir um terminal de comando
- Executar o comando `docker compose up` _(pode levar alguns minutos para montar a imagem e subir os containers)_
- Acessar `localhost:3000` e verificar se foi exibida a mensagem "Hello world"

# Documentação das API's
Todas as API's possuem seu retorno em JSON e também esperam parâmetros enviados em JSON.

A parte que lida com as requisições e estruturação das API's foi toda feita utilizando o framework NextJS, que também utiliza o React como core.

Já o backend foi feito em PHP, utilizando um banco de dados PostgreSQL para persistir os dados das requisições.

Para as requisições é recomendado o uso do método http POST como padrão.

## getCart
Retorna todos os dados do carrinho.

**URL**: `localhost:3000/api/getCart`

**Parâmetros** (JSON): {}

**Retorno**: {}

## addCoupon
Adiciona um cupom de desconto ao carrinho.

**URL**: `localhost:3000/api/addCoupon`

**Parâmetros** (JSON): {}

**Retorno**: {}

## clearCart
Limpa todos os itens e cupons do carrinho.

**URL**: `localhost:3000/api/clearCart`

**Parâmetros** (JSON): {}

**Retorno**: {}

## addItem
Adiciona um item ao carrinho.

**URL**: `localhost:3000/api/addItem`

**Parâmetros** (JSON): {}

**Retorno**: {}

## removeItem
Remove um item do carrinho.

**URL**: `localhost:3000/api/removeItem`

**Parâmetros** (JSON): {}

**Retorno**: {}

## updateItem
Atualiza a quantidade de um item do carrinho.

**URL**: `localhost:3000/api/updateItem`

**Parâmetros** (JSON): {}

**Retorno**: {}
