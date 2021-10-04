const getCartAPI = async function (request, response) {
    const headers = { 'Content-Type': 'application/json' };
    const res = await fetch("http://localhost:80/endpoints/get_cart.php", {
        method: 'POST',
        headers,
        body: JSON.stringify({
            query: request.query
        }),
    });
    const json = await res.json();

    if (json.errors) {
        response.json({});
        throw new Error('Failed to fetch API');
    }

    response.json(json);
}

export default getCartAPI;
