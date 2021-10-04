# Sobre
Desafio de case focado em backend para a Loja Integrada

# Instalação: passo a passo
Passo a passo para clonar o repositório e utilizar o docker compose para subir a aplicação.

## Pré-requisitos:
- Git
- Docker Desktop
- Portas que devem estar livres para que o ambiente faça o deploy com êxito:
  - 5432 - Base de dados PostgreSQL
  - 80 - PHP/Apache
  - 443 - PHP/Apache
  - 3080 - Serviços NodeJS
  - 3000 - Framework NextJS
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
**Parâmetros**: {}
**Retorno**: {}

## addCoupon
Adiciona um cupom de desconto ao carrinho.

**URL**: `localhost:3000/api/addCoupon`
**Parâmetros**: {}
**Retorno**: {}

## clearCart
Limpa todos os itens e cupons do carrinho.

**URL**: `localhost:3000/api/clearCart`
**Parâmetros**: {}
**Retorno**: {}

## addItem
Adiciona um item ao carrinho.

**URL**: `localhost:3000/api/addItem`
**Parâmetros**: Enviar um JSON em formato de string. O nome do parâmetro contendo o JSON deve ser `params` e deve seguir a estrutura: {
  user_id: _id do usuario que adicionou o item ao carrinho_,
  item_code: _código do item_
  item_quantity: _quantidade do item_
}
**Retorno**: {
  status: _inteiro_
  message: _texto_
}

Status:
- 1: Sucesso
- -1: Parâmetros incorretos
- -2: Item não existente no estoque
- -3: Quantidade do item não disponível no estoque
- -4: Item já existe no carrinho
- -5: Não foi possível adicionar o item ao carrinho

## removeItem
Remove um item do carrinho.

**URL**: `localhost:3000/api/removeItem`
**Parâmetros**: {}
**Retorno**: {}

## updateItem
Atualiza a quantidade de um item do carrinho.

**URL**: `localhost:3000/api/updateItem`
**Parâmetros**: {}
**Retorno**: {}
