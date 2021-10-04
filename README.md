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
- Seguir a documentação abaixo para realizar o consumo das API's GET

# Documentação das API's
Todas as API's possuem seu retorno em JSON e também esperam parâmetros enviados em JSON.

A parte que lida com as requisições e estruturação das API's foi toda feita utilizando o framework NextJS, que também utiliza o React como core.

Já o backend foi feito em PHP, utilizando um banco de dados PostgreSQL para persistir os dados das requisições.

Para as requisições é recomendado o uso do método http GET como padrão.

## getCart
Retorna todos os dados do carrinho.

- **URL**: `localhost:3000/api/getCart` 
- **Parâmetros**: {} 
- **Retorno**: {}

## addCoupon
Adiciona um cupom de desconto ao carrinho.

- **URL**: `localhost:3000/api/addCoupon`
- **Parâmetros**: Enviar um JSON em formato de string. O nome do parâmetro contendo o JSON deve ser `params` e deve seguir a estrutura: <pre>{
    user_id: _id do usuario que está vinculado ao carrinho_,
    coupon_code: _código do cupom_
}</pre>
- **Retorno**: <pre>{
    status: _inteiro_
    message: _texto_ 
}</pre>

- **Lista de status**:
  - **1**: Sucesso
  - **-1**: Parâmetros incorretos
  - **-2**: Cupom não existente
  - **-3**: Não foi possível adicionar o cupom ao carrinho

## clearCart
Limpa todos os itens e cupons do carrinho.

- **URL**: `localhost:3000/api/clearCart`
- **Parâmetros**: Enviar um JSON em formato de string. O nome do parâmetro contendo o JSON deve ser `params` e deve seguir a estrutura: <pre>{
    user_id: _id do usuario que está vinculado ao carrinho_
}</pre>
- **Retorno**: <pre>{
    status: _inteiro_
    message: _texto_ 
}</pre>

- **Lista de status**:
  - **1**: Sucesso
  - **-1**: Parâmetros incorretos
  - **-2**: Carrinho não existente
  - **-3**: Não foi possível limpar os itens do carrinho
  - **-4**: Não foi possível limpar o cupom do carrinho

## addItem
Adiciona um item ao carrinho.

- **URL**: `localhost:3000/api/addItem`
- **Parâmetros**: Enviar um JSON em formato de string. O nome do parâmetro contendo o JSON deve ser `params` e deve seguir a estrutura: <pre>{
    user_id: _id do usuario que adicionou o item ao carrinho_,
    item_code: _código do item_,
    item_quantity: _quantidade do item_
}</pre>
- **Retorno**: <pre>{
    status: _inteiro_
    message: _texto_ 
}</pre>

- **Lista de status**:
  - **1**: Sucesso
  - **-1**: Parâmetros incorretos
  - **-2**: Item não existente no estoque
  - **-3**: Parâmetro item_quantity menor ou igual a 0
  - **-4**: Quantidade do item não disponível no estoque
  - **-5**: Item já existe no carrinho
  - **-6**: Não foi possível adicionar o item ao carrinho

## removeItem
Remove um item do carrinho.

- **URL**: `localhost:3000/api/removeItem`
- **Parâmetros**: Enviar um JSON em formato de string. O nome do parâmetro contendo o JSON deve ser `params` e deve seguir a estrutura: <pre>{
    user_id: _id do usuario que adicionou o item ao carrinho_,
    item_code: _código do item_
}</pre>
- **Retorno**: <pre>{
    status: _inteiro_
    message: _texto_ 
}</pre>

- **Lista de status**:
  - **1**: Sucesso
  - **-1**: Parâmetros incorretos
  - **-2**: Carrinho não existe
  - **-3**: Item não existe no carrinho
  - **-4**: Não foi possível remover o item do carrinho

## updateItem
Atualiza a quantidade de um item do carrinho.

- **URL**: `localhost:3000/api/updateItem`
- **Parâmetros**: {}
- **Retorno**: {}
