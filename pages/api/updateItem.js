const UpdateItemAPI = async function (request, response) {
    const headers = { 'Content-Type': 'application/json' };
    const res = await fetch("http://localhost:80/endpoints/update_item_quantity.php", {
        method: 'POST',
        headers,
        body: JSON.stringify({
            query: request.query
        }),
    });
    const json = await res.json();

    if (json.errors) {
        response.json({});
        throw new Error('Failed to fetch Update Item Quantity API');
    }

    response.json(json);
}

export default UpdateItemAPI;
