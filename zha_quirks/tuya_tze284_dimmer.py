from zhaquirks.tuya.ts0601_dimmer import TuyaDoubleSwitchDimmerGP, TuyaSingleSwitchDimmerGP

# Single-channel dimmer quirk
class TuyaTZE284SingleDimmer(TuyaSingleSwitchDimmerGP):
    """Tuya TZE284 single dimmer quirk."""

    signature = {
        "manufacturer": "_TZE284_nqqylykc",
        "model": "TS0601",
        "endpoints": {
            #  <SimpleDescriptor endpoint=1 profile=260 device_type=81
            #  input_clusters=[0, 4, 5, 61184, 61440]
            #  output_clusters=[10, 25]>
            1: {
                "profile_id": 260,
                "device_type": 81,
                "input_clusters": [0, 4, 5, 0xED00, 0xEF00],
                "output_clusters": [10, 25],
            },
            #  <SimpleDescriptor endpoint=242 profile=41440 device_type=97
            #  input_clusters=[]
            #  output_clusters=[33]>
            242: {
                "profile_id": 0xA1E0,
                "device_type": 97,
                "input_clusters": [],
                "output_clusters": [33],
            },
        },
    }


# Double-channel dimmer quirk
class TuyaTZE284DoubleDimmer(TuyaDoubleSwitchDimmerGP):
    """Tuya TZE284 dual dimmer quirk."""

    signature = {
        "manufacturer": "_TZE284_jtbgusdc",
        "model": "TS0601",
        "endpoints": {
            #  <SimpleDescriptor endpoint=1 profile=260 device_type=81
            #  input_clusters=[0, 4, 5, 61184, 61440]
            #  output_clusters=[10, 25]>
            1: {
                "profile_id": 260,
                "device_type": 81,
                "input_clusters": [0, 4, 5, 0xED00, 0xEF00],
                "output_clusters": [10, 25],
            },
            #  <SimpleDescriptor endpoint=242 profile=41440 device_type=97
            #  input_clusters=[]
            #  output_clusters=[33]>
            242: {
                "profile_id": 0xA1E0,
                "device_type": 97,
                "input_clusters": [],
                "output_clusters": [33],
            },
        },
    }




# from zhaquirks.tuya.ts0601_dimmer import TuyaDoubleSwitchDimmerGP, TuyaSingleSwitchDimmerGP




# class TuyaTZE284DoubleDimmer(TuyaDoubleSwitchDimmerGP):
#     """Tuya TZE284 dual dimmer quirk."""

#     signature = {
#         "manufacturer": "_TZE284_jtbgusdc",
#         "model": "TS0601",
#         "endpoints": {
#             #  <SimpleDescriptor endpoint=1 profile=260 device_type=81
#             #  input_clusters=[0, 4, 5, 61184, 61440]
#             #  output_clusters=[10, 25]>
#             1: {
#                 "profile_id": 260,
#                 "device_type": 81,
#                 "input_clusters": [0, 4, 5, 0xED00, 0xEF00],
#                 "output_clusters": [10, 25],
#             },
#             #  <SimpleDescriptor endpoint=242 profile=41440 device_type=97
#             #  input_clusters=[]
#             #  output_clusters=[33]>
#             242: {
#                 "profile_id": 0xA1E0,
#                 "device_type": 97,
#                 "input_clusters": [],
#                 "output_clusters": [33],
#             },
#         },
#     }

#     # The replacement dictionary is inherited from TuyaDoubleSwitchDimmerGP
#     # so it does not need to be redefined here unless you need to override it.