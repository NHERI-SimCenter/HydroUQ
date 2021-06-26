---
title: 'HydroUQ: Open-source application for modeling water-borne natural hazards'
tags:
- Python
- CFD
- OpenFOAM
- numerical methods
- finite volume
authors:
- name: Ajay B. Harish
  orcid: 0000-0001-5234-7047
  affiliation: "1, 2"
- name: Sanjay Govindjee
  orcid: 0000-0003-0711-3633
  affiliation: "1, 2"
- name: Frank McKenna
  affiliation: 2

affiliations:
- name: Department of Civil and Environmental Engineering, University of California, Berkeley, CA (USA)
  index: 1
- name: NHERI SimCenter, University of California, Berkeley, CA (USA)
  index: 2
date: 18 Jun 2021
bibliography: paper.bib
---

# Introduction and motivation

Natural disasters, like tsunamis and storm surges, are often unpredictable in their timing and cause substantial loss of life and property during the occurrence. Due to complex climate dynamics and rising sea levels, the changing landscape has made these extreme events more frequent and deadly [@Knetal2010], [@Heetel2013], [@Koetal2014]. Once in a decade, devastating events are occurring more frequently with larger intensities. There has been a substantial uptick in the number of residents in the coastal areas and this is expected to rise over the coming decades. Costal hazard events have caused hundreds of billions of dollars in damage over the recent decades, destroyed communities and commerce, caused fatalities, distrupted the quality of life in these regions. In addition, coastal hazard impact tends to fall disproportionately on economically disadvantaged members of an affected community, with income inequality increasing an average of 5.4% for every $100. It is not just the coastal population. Even the coastlines are under threat in both short and long term. In the short term of a decade, coastlines are under the threat of chronic erosion in Florida, Mississippi Delta, North Carolina and many other locations [@Toetal2006], [@Moetal2018], [@Joetal2009]. In the long term, the impending sea level rise will lead to wholesale relocation of coastal population, including abandonment of many areas. The secondary effects that include changes to morphology and erosion will continue to directly impact commerce in coastal areas. In this regard, the disaster reconnaissance investigations of previous events has proved useful and provided ways to understand and improve the scientific understanding of these extreme events. However, the grand challenge today [@StateArtRepo2021], [@SCPaper2020], [@RAPID2020] is to being able to model hazards probabilistically and predict the risk to the urban environment and community. Thus, the development of such high-fidelity tools that provide stochastic solutions are much necessary in order to evaluate decisions that enhance overall community resilience.

## Storm surge

When severe storms like hurricanes, tropical cyclones, etc., move towards the land, the low pressure and strong winds force the ocean water to rise and move towards the coastal regions. These tides can produce water levels much higher than normal tides. As these waves reach the coast and the depth of water decreases, it can significantly increase the waves’ amplitude. When a storm surge arrives simultaneously as the astronomical high tide, it can raise water levels to as much as 20 feet or more beyond the mean sea level. While the wave velocity is small, the water has a density of 1000 kg per cubic meter. The continued impact of storm surge water can significantly damage property, eroding coasts, etc. It has been found that the storm surge is related to hurricane intensity, coastal geography, size/speed/angle of approach of the hurricane, among other things. Many studies have investigated the impact of climate change on tropical cyclones, and most agree that the maximum wind speeds and minimum pressures will intensify by 5% for every one deg-C temperature increase in the tropical ocean temperature [@Em1987]. [NOAA’s National Hurricane Center](https://www.arcgis.com/apps/MapSeries/index.html?appid=d9ed7904dbec441a9c4dd7b277935fad) offers a series of maps that can help people identify hurricane-prone areas, particularly related to the eastern seaboard of continental US.

## Tsunami

While storm surges have been of significant importance to the eastern seaboard, tsunamis threaten the pacific coastline. Tsunamis that caused catastropic damage were believed to be once in a century event but not anymore. We have already had three deadly events (Indian ocean 2004, Chile 2010 and Tohoku 2011) in the early part of the 21st century. Each of these caused unprecedented damage to the coastal communities in different parts of the world. Tsunamis are rare events that are often accompanied by advanced warnings. It is not possible to predict where and when the subsequent Tsunami might occur. However, tsunami warning centers know which events could likely generate tsunamis and issue warnings. This is done through networks of the ocean and coastal sea-level observation systems designed to detect tsunamis. These early-warning systems facilitate evacuation to areas of high ground outside of the tsunami inundation regions. Often when tsunamis are triggered by distant events, which allows for longer evacuation times, the coastal communities can be evacuated. When this is triggered by local events, there might not be sufficient time for a horizontal evacuation. In such scenarios, a potential solution is a vertical evacuation above the rising waters into high-rise buildings and other structures with the strength and resilience necessary to resist the effects of tsunami waves [@Andrew2021], [@Tsunami2021]. One of the essential aspects is related to the measurement of Tsunami. Three definitions are considered for the water level. The first is the “Inundation height.” The inundation height is the height from the average water level to the top of the flooded water level. The second measure is the “Inundation depth.” This is the distance from the ground surface to the top of the flooded water level. The last measure is known as the “Run-up height.” This is the height of the average water level to the water level where the Tsunami stops. This is important to gauge the overall tsunami energy.

# Statement of need



## Fieldwork and experiments
In order to understand the effects of coastal hazards, both field work and scaled experiments using a wave flume have been used. 



[@cox2008a], [@lindt2009a], [@rueben2011a], [@shin2012a], [@park2013a]

The **HydroUQ** is an open-source cloud-based application that provides researchers a tool to assess the performance of a building or specimen subjected to wave loading during natural hazard events, namely tsunami and storm surge . 


Effective prediction of tidal storm or tsunami waves is important to safeguard important infrastructure like ports, bridges and high-rise evacuation structures. During such water-borne hazard events, it is believe that vertical evacuation structures, within the predicted inundation zones, could provide refuge to people. Such structures need to be capable of withstanding the forces due to wave impact. Thus, it becomes important to consider the urban environment, including all the buildings, around such structures to evaluate the flow fields and forces accurately.

Tsunami and storm-surge modeling widely uses shallow-water solutions to determine the inundation heights, and maximum runup heights. Such methodologies are largely restricted to smoother topographies and cannot accurately consider flows around the complex built urban environment [@Mike2018]. Thus, high-fidelity 3-D CFD simulations are required for structures into the coast.

HydroUQ serves two of the paramount needs in the civil, structural and coastal engineering community, namely (a) Multiscale fluids modeling (b) Wave flume digital twin.

## Multiscale fluids modeling

A more detailed discussion on the results and validation of the multiscale fluids model is available in [@Ajay2021a].

## Wave flume digital twin

A more detailed discussion on the results and validation of the wave flume digital twin is available in [@Ajay2021b].

# Features and design


# Conclusions

HydroUQ provides a novel architecture for the coastal engineering community to understand water-borne hazards.

# Acknowledgements

The SimCenter was financially supported by the National Science Foundation under Grant CMMI-1612843. Any opinions, findings, and conclusions or recommendations expressed in this material are those of the authors and do not necessarily reflect the views of the National Science Foundation. We would like to acknowledge (1) the contributions and collaboration with many faculty, post-doctoral researchers, students and staff who have contributed to the SimCenter’s work, and (2) the support and close collaboration with DesignSafe, which facilitates access to high-performance computing and information technologies for SimCenter tools.

# References
