{
    "connections": [
        {
            "in_id": "{005670ce-e7bc-4fda-8cf6-e9e3d6de64ba}",
            "in_index": 0,
            "out_id": "{6a20fe15-427d-4bfc-a82c-03687046b408}",
            "out_index": 0
        },
        {
            "in_id": "{6a20fe15-427d-4bfc-a82c-03687046b408}",
            "in_index": 0,
            "out_id": "{e51ab492-2d43-4b1a-85ac-4c1276ab8e4e}",
            "out_index": 0
        },
        {
            "in_id": "{b3f647ac-76a3-46ee-8cd8-67f0c72c1282}",
            "in_index": 0,
            "out_id": "{79165216-42e0-49e0-ba62-29136b92092b}",
            "out_index": 0
        },
        {
            "in_id": "{e51ab492-2d43-4b1a-85ac-4c1276ab8e4e}",
            "in_index": 0,
            "out_id": "{b3f647ac-76a3-46ee-8cd8-67f0c72c1282}",
            "out_index": 0
        }
    ],
    "nodes": [
        {
            "id": "{6a20fe15-427d-4bfc-a82c-03687046b408}",
            "model": {
                "CAN database": null,
                "caption": "CanSignalDecoder #5",
                "color": "#9CD59B",
                "name": "CanSignalDecoder"
            },
            "position": {
                "x": 230.99922839506172,
                "y": 34.239969135802475
            }
        },
        {
            "id": "{005670ce-e7bc-4fda-8cf6-e9e3d6de64ba}",
            "model": {
                "caption": "CanSignalViewer #6",
                "name": "CanSignalViewer"
            },
            "position": {
                "x": 476.46604938271605,
                "y": 76.19598765432103
            }
        },
        {
            "id": "{79165216-42e0-49e0-ba62-29136b92092b}",
            "model": {
                "CAN database": null,
                "caption": "CanSignalSender #4",
                "color": "#9CD59B",
                "name": "CanSignalSender",
                "rows": [
                    {
                        "id": "0x200",
                        "sig": "BrakeLightON_CTRL",
                        "val": "0"
                    }
                ]
            },
            "position": {
                "x": -542.8799999999998,
                "y": 51.839999999999975
            }
        },
        {
            "id": "{b3f647ac-76a3-46ee-8cd8-67f0c72c1282}",
            "model": {
                "CAN database": "{76e096ae-d08f-497e-89eb-cb52a1c6cc1b}",
                "caption": "CanSignalEncoder #3",
                "color": "#9CD59B",
                "name": "CanSignalEncoder"
            },
            "position": {
                "x": -328.5227777777776,
                "y": 41.26422839506169
            }
        },
        {
            "id": "{e51ab492-2d43-4b1a-85ac-4c1276ab8e4e}",
            "model": {
                "backend": "socketcan",
                "caption": "CanDevice #1",
                "configuration": "",
                "interface": "can0",
                "name": "CanDevice"
            },
            "position": {
                "x": -14,
                "y": 29
            }
        },
        {
            "id": "{76e096ae-d08f-497e-89eb-cb52a1c6cc1b}",
            "model": {
                "caption": "CanSignalData #2",
                "color": "#9CD59B",
                "file": "/home/simone/Documents/0.2-SC/SCan/SC22EVO/artifacts/MCB/MCB.dbc",
                "msgSettings": [
                ],
                "name": "CanSignalData"
            },
            "position": {
                "x": 0,
                "y": 186
            }
        }
    ]
}
